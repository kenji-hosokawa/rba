/**
 * Copyright (c) 2019 DENSO CORPORATION.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 /**
 * Arbitrator class definition
 */

#include <algorithm>
#include <sstream>
#include "RBAArbitrator.hpp"
#include "RBAModelImpl.hpp"
#include "RBAResult.hpp"
#include "RBAResultSet.hpp"
#include "RBAAffectInfo.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAViewAction.hpp"
#include "RBAViewTransition.hpp"
#include "RBAViewMove.hpp"
#include "RBARollbacker.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba {

RBAArbitrator::RBAArbitrator(RBAModel* newModel)
{
  setModel(newModel);
}

#ifdef RBA_USE_LOG
RBAArbitrator::RBAArbitrator(RBAModel* newModel, RBALogManager* logManager)
{
  setModel(newModel);
  RBALogManager::setLogManager(logManager);
  // Even if the argument logManager is null, it may be setLogManager() 
  // from outside the rba, so it is determined by getLogManager() instead of 
  // the argument determination.
  if (RBALogManager::getLogManager() != nullptr) {
    setSimulationMode(true);
  }
}
#endif

RBAArbitrator::~RBAArbitrator() noexcept
{
}

void
RBAArbitrator::setModel(RBAModel* newModel)
{
  setModel(dynamic_cast<RBAModelImpl*>(newModel));
}

const RBAModel*
RBAArbitrator::getModel() const
{
  return dynamic_cast<RBAModel*>(model_);
}

void
RBAArbitrator::initialize(std::list<std::string>& contexts)
{
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  setRequestData(contexts, true);
}

std::unique_ptr<RBAResult>
RBAArbitrator::execute(const std::string& contextName, bool require)
{
  const std::lock_guard<std::recursive_mutex> lock {getMutex()};
  if (isValidContext(contextName) == false) {
    // In case of error, creates a copy of "Result", 
    // sets the error flag in it and returns
    std::unique_ptr<RBAResultImpl> result {std::make_unique<RBAResultImpl>(
        this, std::make_unique<RBAResultSet>(*getBackupResultSet()))};
    result->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(result);
  } else {
    static_cast<void>(setRequestData(contextName, require, nullptr,
                      static_cast<std::uint32_t>(getRequestQue().size())));
    return arbitrateMain();
  }
}

std::unique_ptr<RBAResult>
RBAArbitrator::execute(std::list<std::string>& contexts,
		       bool require)
{
  const std::lock_guard<std::recursive_mutex> lock {getMutex()};
  if (isValidContext(contexts) == false) {
    // In case of error, creates a copy of "Result", 
    // sets the error flag in it and returns
    std::unique_ptr<RBAResultImpl> result {std::make_unique<RBAResultImpl>(
        this, std::make_unique<RBAResultSet>(*getBackupResultSet()))};
    result->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(result);
  } else {
    setRequestData(contexts, require);
    return arbitrateMain();
  }
}

std::unique_ptr<RBAResult>
RBAArbitrator::execute(const std::string& sceneName,
		       std::list<std::pair<std::string,std::int32_t>>& properties)
{
  const std::lock_guard<std::recursive_mutex> lock {getMutex()};
  // Check argument
  if (isValidContext(sceneName) == false) {
    // In case of error, creates a copy of "Result", 
    // sets the error flag in it and returns
    std::unique_ptr<RBAResultImpl> result {std::make_unique<RBAResultImpl>(
        this, std::make_unique<RBAResultSet>(*getBackupResultSet()))};
    result->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(result);
  } else {
    static_cast<void>(setRequestData(sceneName, true, &properties,
                      static_cast<std::uint32_t>(getRequestQue().size())));
    return arbitrateMain();
  }
}

std::unique_ptr<RBAResult>
RBAArbitrator::setResultContentState(const std::string& allocatableName,
				     const std::string& contextName)
{
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  RBAResultSet* const backupResultSetTmp {getBackupResultSet().get()};
  if (getReservedResultSet() == nullptr) {
    setResult(std::make_unique<RBAResultImpl>(this,
                                              std::make_unique<RBAResultSet>(),
                                              std::move(getBackupResultSet())));
  } else {
    RBAResultSet* const reservedResultSetTmp {getReservedResultSet().get()};
    setResult(std::make_unique<RBAResultImpl>(this,
                                              std::move(getReservedResultSet()),
                                              std::move(getBackupResultSet())));
    setReservedResultSet(std::make_unique<RBAResultSet>(*reservedResultSetTmp));
  }
  setBackupResultSet(std::make_unique<RBAResultSet>(*backupResultSetTmp));
  
  // find allocatable
  const RBAAllocatable* alloc {nullptr};
  const RBAAreaImpl* const area {model_->findAreaImpl(allocatableName)};
  if(area != nullptr) {
    alloc = area;
  }
  else {
    const RBAZoneImpl* const zone {model_->findZoneImpl(allocatableName)};
    if(zone != nullptr) {
      alloc = zone;
    }
  }
  // find content state
  const RBAContentState* state {nullptr};
  const RBAViewContentStateImpl* const viewState
    {model_->findViewContentStateImpl(contextName)};
  if(viewState != nullptr) {
    state = viewState;
  }
  else {
    const RBASoundContentStateImpl* const soundState
      {model_->findSoundContentStateImpl(contextName)};
    if(soundState != nullptr) {
      state = soundState;
    }
  }
  if( (alloc == nullptr) || (state == nullptr) ) {
    // Unknown context or allocatable
    getResult()->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(getResultRef());
  }
  // Set alloc and state to result
  const RBAContentState* const beforeContentState {alloc->getState()};
  const_cast<RBAAllocatable*>(alloc)->setState(state);
  const_cast<RBAAllocatable*>(alloc)->setChecked(true);
  getResult()->setActive(state, true);
  getResult()->setContentState(alloc, state);

  // ----------------------------------------------------------
  // Post processing of Arbitration
  // ----------------------------------------------------------
  postArbitrate();

  // Excecute offline constraint
#ifdef RBA_USE_LOG
  checkAllConstraints();
#endif

  // ----------------------------------------------------------
  // Update the state of Content
  // ----------------------------------------------------------
  if (beforeContentState != nullptr) {
    // Update the state of the Content originally assigned to 
    // the requested Allocatable
    dynamic_cast<RBAContent*>(beforeContentState->getOwner())->updateStatus(getResultRef().get());
  }
  // Update the state of requested Content
  dynamic_cast<RBAContent*>(state->getOwner())->updateStatus(getResultRef().get());

  // Cancel processing of Content
  checkCancelContent();

  // Update display and non-display Area
  updateResult();

  // Generate Result
  createResultData();

  // Store backup of current arbitration result set
  setBackupResultSet(getResult()->createBackupCurrentResultSet());
  // Create next arbitration result set
  setNextResultSet(getResult()->createNextCurrentResultSet());

  return std::move(getResultRef());
}

std::unique_ptr<RBAResult>
RBAArbitrator::cancelArbitration()
{
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  if(getReservedResultSet() == nullptr) {
    std::unique_ptr<RBAResultImpl> res
      {std::make_unique<RBAResultImpl>(this,
                                       std::make_unique<RBAResultSet>())};
    res->setStatusType(RBAResultStatusType::CANCEL_ERROR);
    return std::move(res);
  }

  setResult(
      std::make_unique<RBAResultImpl>(this,
                                      std::make_unique<RBAResultSet>(),
                                      std::move(getReservedResultSet())));
  setBackupResultSet(getResult()->createBackupCurrentResultSet());
  setNextResultSet(getResult()->createNextCurrentResultSet());

  return std::move(getResultRef());
}

void
RBAArbitrator::clearArbitration()
{
  std::lock_guard<std::recursive_mutex> lock {getMutex()};
  getCancelChecked().clear();
  setReservedResultSet(nullptr);
  setBackupResultSet(std::make_unique<RBAResultSet>());
  for(const auto& scene : model_->getSceneImpls()) {
    for(const std::string propertyName : scene->getPropertyNames()) {
      const std::int32_t value {scene->getPropertyValue(propertyName)};
      getBackupResultSet()->setSceneProperty(scene, propertyName, value);
    }
  }
  setNextResultSet(
      std::make_unique<RBAResultSet>(*getBackupResultSet().get()));
  setResult(std::make_unique<RBAResultImpl>(
      this,
      std::make_unique<RBAResultSet>(*getBackupResultSet().get())));

  model_->clearElementsStatus();
}

bool
RBAArbitrator::setScene(const std::string& sceneName, bool require,
			std::list<std::pair<std::string, std::int32_t>>& properties)
{
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  return setRequestData(sceneName, require, &properties);
}

bool
RBAArbitrator::setContentState(const std::string& contextName, bool require)
{
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  const std::deque<std::unique_ptr<RBARequestQueMember>>& requestQue{getRequestQue()};
  std::uint32_t syncIndex{static_cast<std::uint32_t>(requestQue.size())};
  if (syncIndex > 0U ) {
    const std::unique_ptr<RBARequestQueMember>& prevReq{requestQue.back()};
    if (prevReq->isOn() == require) {
      syncIndex = prevReq->getSyncIndex();
    }
  }
  return setRequestData(contextName, require, nullptr, syncIndex);
}

bool
RBAArbitrator::setAllocatableResult(const std::string& allocatableName,
				    const std::string& contextName)
{
  std::lock_guard<std::recursive_mutex> lock {getMutex()};
  // Get allocatable
  const auto alloc = model_->findAllocatable(allocatableName);
  if(alloc == nullptr) {
    return false;
  }

  // Get context
  const auto state = model_->findContentState(contextName);
  if(state == nullptr) {
    return false;
  }

  // Set state to allocatable
  const auto beforeContentState = alloc->getState();
  const_cast<RBAAllocatable*>(alloc)->setState(state);
  RBAResultSet* const nextResultSet {getNextResultSet().get()};
  RBAResultSet* const prevResultSet {getBackupResultSet().get()};
  nextResultSet->setContentState(alloc, state);
  prevResultSet->setContentState(alloc, state);
  nextResultSet->setActive(state, true);
  prevResultSet->setActive(state, true);

  // ----------------------------------------------------------
  // Update the state of Content
  // ----------------------------------------------------------
  // Create "result" and update state, because updating the content state 
  // determines the transition destination this time 
  // based on previous state.
  setResult(std::make_unique<RBAResultImpl>(
      this,
      std::make_unique<RBAResultSet>(*getBackupResultSet()),
      std::make_unique<RBAResultSet>(*getNextResultSet())));
  RBAContent* const content {dynamic_cast<RBAContent*>(state->getOwner())};
  content->updateRequestStatus(getResult()->getCurResultSet().get(), true);
  if (beforeContentState != nullptr) {
    // Update the state of the content originally assigned to 
    // the requested Allocatable
    dynamic_cast<RBAContent*>(beforeContentState->getOwner())->updateStatus(getResultRef().get());
  }
  // Update the state of requested Content
  content->updateStatus(getResultRef().get());

  setBackupResultSet(std::make_unique<RBAResultSet>(*getResult()->getPreResultSet()));
  setNextResultSet(getResult()->createNextCurrentResultSet());

  return true;
}

bool
RBAArbitrator::RBAArbitrator::evaluate(RBAExpression* expression)
{
  if(expression == nullptr) {
    return false;
  }
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  RBAConstraintInfo info;
  // Constraint expression evaluation
  return expression->execute(&info, this);
}

const RBARuleObject*
RBAArbitrator::evaluateObject(RBAExpression* expression)
{
  if(expression == nullptr) {
    return nullptr;
  }
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  RBAConstraintInfo info;
  // Constraint expression evaluation
  const RBARuleObject* const ruleObj
    {expression->getReferenceObject(&info, this)};
  if (ruleObj != nullptr) {
    return ruleObj->getRawObject();
  } else {
    return nullptr;
  }
}

int32_t
RBAArbitrator::evaluateValue(RBAExpression* expression)
{
  if(expression == nullptr) {
    return -99;
  }
  const std::lock_guard<std::recursive_mutex> lock{getMutex()};
  RBAConstraintInfo info;
  // Constraint expression evaluation
  return expression->getValue(&info, this);
}


void
RBAArbitrator::setModel(RBAModelImpl* const newModel)
{
  std::lock_guard<std::recursive_mutex> lock {getMutex()};
  model_ = newModel;
  model_->createSortedAllocatables();
  clearArbitration();
}

bool
RBAArbitrator::
satisfiesConstraints() const
{
  const std::lock_guard<std::recursive_mutex> lock{mutex_};
  // Temporarily store the actual result_ 
  // because result_ is used for evaluation
  std::unique_ptr<RBAResultImpl> tmpResult {std::move(result_)};
  result_ = std::make_unique<RBAResultImpl>(
      this,
      std::make_unique<RBAResultSet>(*(reservedResultSet_.get())),
      std::make_unique<RBAResultSet>(*(resultSetForSatisfiesConstraints_.get())));
  bool result {true};
  for(const RBAConstraintImpl*& constraint : model_->getConstraintImpls()) {
    if (constraint->isRuntime() == true) {
      result = const_cast<RBAConstraintImpl*>(constraint)->execute(const_cast<RBAArbitrator*>(this));
      if (result == false) {
        break;
      }
    }
  }
  result_ = std::move(tmpResult);
  return result;
}

/**
 * Execute arbitration
 */
std::unique_ptr<RBAResult>
RBAArbitrator::arbitrateMain()
{
  // Store request state before arbitration, 
  // in case cancelArbitration() is executed
  reservedResultSet_ = std::make_unique<RBAResultSet>(*backupResultSet_);

  // Differential arbitration for each request
  if (requestQue_.empty()) {
    // Prepare Result here because it will be used in differenceArbitrate.
    result_ = std::make_unique<RBAResultImpl>(this,
                                              std::move(backupResultSet_),
                                              std::move(nextResultSet_));
    // Arbitration request without arguments.
    // there is a possibility of being queued in "requestQue_"
    // due to "onDisplayed" in this, 
    differenceArbitrate();
  }
  if (!requestQue_.empty()) {
    result_ = std::make_unique<RBAResultImpl>(this,
                                              std::move(backupResultSet_),
                                              std::move(nextResultSet_));
    do {
      const std::unique_ptr<RBARequestQueMember> request {std::move(requestQue_.front())};
      requestQue_.pop_front();
      result_->setActive(request->getContentState(), request->isOn());
      // Update the state of Content
      RBAContent* const content {dynamic_cast<RBAContent*>(request->getContentState()->getOwner())};
      content->updateRequestStatus(result_->getCurResultSet().get(), request->isOn());
      if (requestQue_.empty()) {
        differenceArbitrate();
        if (!requestQue_.empty()) {
          // Update "result_" for the next differenceArbitrate().
          result_ = std::make_unique<RBAResultImpl>(this,
                                                    std::move(backupResultSet_),
                                                    std::move(nextResultSet_));
        }
      } else if (requestQue_.front()->getSyncIndex() != request->getSyncIndex()) {
        differenceArbitrate();
        // Update "result_" for the next differenceArbitrate().
        result_ = std::make_unique<RBAResultImpl>(this,
                                                  std::move(backupResultSet_),
                                                  std::move(nextResultSet_));
      } else {
        // No Operation
      }
    } while (!requestQue_.empty());
  }

  result_ = std::make_unique<RBAResultImpl>(
      this, std::make_unique<RBAResultSet>(*reservedResultSet_),
      result_->createBackupCurrentResultSet());

  // Cancel processing of Content
  checkCancelContent();

  // Update displayed and non-displayed Area
  updateResult();

#ifdef RBA_USE_LOG
  RBALogManager::setType(RBALogManager::TYPE_RESULT);
  logResultArbitration();

  setLogToResult();
  RBALogManager::setType(RBALogManager::TYPE_NOTHING);
#endif

  createResultData();
  // Store backup of current arbitration result set
  backupResultSet_ = result_->createBackupCurrentResultSet();
  // Create next arbitration result set
  nextResultSet_ = result_->createNextCurrentResultSet();

  // The "result_" of the return value is changed to another name,
  // because "result_" will be used for storing.
  auto retResult = std::move(result_);

  // Hold the arbitration result because the arbitration result may be used 
  // in cases other than arbitration.
  result_ = std::make_unique<RBAResultImpl>(retResult.get());

  // A compile error occurs if std::move() is missing because 
  // std::unique_ptr<RBAResultImpl>　is cast to std::unique_ptr<RBAResult>
  return std::move(retResult);
}

bool
RBAArbitrator::
isValidContext(const std::string& context)
{
  if (context != "") {
    const RBAContentState* const state {model_->findContentState(context)};
    if (state == nullptr) {
      const RBASceneImpl* const scene {model_->findSceneImpl(context)};
      if (scene == nullptr) {
        return false;
      }
    }
  }

  return true;
}

bool
RBAArbitrator::
isValidContext(std::list<std::string>& contexts)
{
  for(const std::string contextName : contexts) {
    if(isValidContext(contextName) == false) {
      return false;
    }
  }

  return true;
}

/**
 * Reflect input information
 */

bool
RBAArbitrator::setRequestData(
    const std::string& context, bool require,
    std::list<std::pair<std::string, std::int32_t>>* const properties,
    std::uint32_t syncIndex)
{
  bool isSet {false};
  if (context != "") {
    // When content state is specified
    // If contextName is the only content name, pop the first content state
    const RBAContentState* state {model_->findContentState(context)};
    if (state != nullptr) {
      requestQue_.push_back( std::make_unique<RBARequestQueMember>(state, require, syncIndex));
      isSet = true;
    } else {
      // When Scene is specified
      const RBASceneImpl* const scene {model_->findSceneImpl(context)};
      if (scene != nullptr) {
        // for next arbitration
        nextResultSet_->setActive(scene, require);
        // For when "Result" is referenced before the next arbitration
        result_->setActive(scene, require);
        isSet = true;
        if (properties != nullptr) {
          for (auto& p : *properties) {
            const RBAAbstractProperty* const ap {scene->getProperty(p.first)};
            if (ap != nullptr) {
              // for next arbitration
              nextResultSet_->setSceneProperty(ap, p.second);
              // For when "Result" is referenced before the next arbitration
              result_->setSceneProperty(ap, p.second);
            }
          }
        }
      }
    }
  }
  return isSet;
}

void
RBAArbitrator::setRequestData(const RBAContentState* state,
                                  bool require)
{
  if (requestQue_.empty()){
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(state, require, 0U));
  } else {
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(state, require, requestQue_.back()->getSyncIndex()));
  }
}

void
RBAArbitrator::setRequestData(const RBAContent* const content,
                                  bool require)
{
  if (requestQue_.empty()){
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(content->getStates().front(), require, 0U));
  } else {
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(content->getStates().front(), require, requestQue_.back()->getSyncIndex()));
  }
}

void
RBAArbitrator::setActive(const RBASceneImpl* const scene, const bool require)
{
  if (nextResultSet_ != nullptr) {
    // Update nextResultSet_" when onScene is done in onRequest or onWithdrawn
    nextResultSet_->setActive(scene, require);
  } else {
    result_->setActive(scene, require);
  }
}

void
RBAArbitrator::setSceneProperty(const RBAAbstractProperty* const prop, const std::int32_t value)
{
  if (nextResultSet_ != nullptr) {
    // Update nextResultSet_" when onScene is done in onRequest or onWithdrawn
    nextResultSet_->setSceneProperty(prop, value);
  } else {
    result_->getCurResultSet()->setSceneProperty(prop, value);
  }
}

void
RBAArbitrator::setRequestData(std::list<std::string>& contexts,
                              const bool require)
{
  const std::uint32_t syncIndex {static_cast<std::uint32_t>(requestQue_.size())};
  for (auto& c : contexts) {
    static_cast<void>(setRequestData(c, require, nullptr, syncIndex));
  }
}

/**
 * @brief Execute an extended version of arbitration that allows arbitration 
          when the "implication" is false
 * @param areas
 */
void
RBAArbitrator::
arbitrate(std::list<RBAAllocatable*>& allocatables)
{
  LOG_arbitrateAreaLogLine("----Arbitrate----");
  std::set<const RBAAllocatable*> revisitedInitSet;

  std::set<const RBAAllocatable*> revisited;
  for (auto& alloc : allocatables) {
    revisited = revisitedInitSet;
    // -------------------------------------------------------------------------
    // To prevent an infinite loop, generate information to limit registration 
  　　// of other "allocable" that affected the target "allocatable" 
    // during arbitration
    // -------------------------------------------------------------------------
    RBAAffectInfo affectInfo;
    LOG_arbitrateAreaLogLine(
        alloc->getSymbol() + "[" + alloc->getElementName() + "] check start");
    arbitrateAllocatable(alloc, revisited, 0, &affectInfo, nullptr);
  }
  for (auto& a : model_->getSortedAllocatables()) {
    result_->setContentState(a, a->getState());
  }
}

/**
 * @brief Recursively arbitrate "allocatable"
 * @param allocatable Allocatable that you want to arbitrate
 * @param revisited Allocatable that re-arbitration is complete
 * @param nest Re-arbitration nesting hierarchy (first arbitration is zero)
 * @param affectInfo Allocatable information affected by "allocatable"
 */
void RBAArbitrator::arbitrateAllocatable(
    RBAAllocatable* allocatable,
    std::set<const RBAAllocatable*>& revisited,
    const std::int32_t nest,
    RBAAffectInfo* const affectInfo,
    RBARollbacker* const parentRollbacker)
{
#ifdef RBA_USE_LOG
  RBALogManager::setIndent(nest);
#endif
  // "Allocable" affected by "Allocable" which is the target of this arbitration
  // during the recursive process until this variable is defined,
  std::set<const RBAAllocatable*> affectAllocatables;
  affectAllocatables.insert(allocatable->getAllocatablesAffectedByYou().begin(),
                            allocatable->getAllocatablesAffectedByYou().end());

  const RBAContentState* const beforeState {allocatable->getState()};

  // Mark Content allocation for target Allocable" as "checked"
  allocatable->setChecked(true);
  // Get content status sorted by arbitration policy
  // (only active requests)
  std::list<const RBAContentState*> contentStates;
  getSortedContentStates(allocatable, contentStates);
  for(const RBAContentState* const contentState : contentStates) {
    // Allocate Content to Area
    allocatable->setState(contentState);
#ifdef RBA_USE_LOG
    {
      std::string str = "  Content[";
      if (contentState == nullptr) {
        str += "null";
      } else {
        str += contentState->getOwner()->getElementName() + "::"
            + contentState->getElementName();
      }
      str += "] check online constraints start";
      RBALogManager::arbitrateContentLogLine(str);
    }
#endif
    bool isSkipped {false};
    const bool isPassed {checkConstraintAndReArbitrate(
        allocatable, revisited, nest, affectInfo, parentRollbacker,
        allocatable->getConstraints(), &isSkipped, false)};
    if (isPassed == true) {

      // ----------------------------------------------------------
      // Check if self-allocatable should be hidden 
      // by constraint expression after content allocation process.
      // Check even if content is not assigned because there is contentValue()
      // ----------------------------------------------------------
#ifdef RBA_USE_LOG
      std::string alloSymbol = allocatable->getSymbol();
      std::string alloName = allocatable->getElementName();
      if (allocatable->isArea() == true) {
        LOG_arbitrateAreaLogLine(
            "  check online constraints to confirm area hidden state");
      } else {
        LOG_arbitrateAreaLogLine(
            "  check online constraints to confirm zone muted state");
      }
#endif
      // Mark "hidden" of target "Allocable" as "checked"
      allocatable->setHiddenChecked(true);
      // Set "hidden" of target "Allocable" to false
      allocatable->setHidden(false);
      bool hiddenIsPassed {checkConstraintAndReArbitrate(
          allocatable, revisited, nest, affectInfo, parentRollbacker,
          allocatable->getHiddenFalseCheckConstraints(), &isSkipped, 
          !allocatable->isZone())};
      if (hiddenIsPassed == false) {
        allocatable->setHidden(true);
        hiddenIsPassed = checkConstraintAndReArbitrate(
            allocatable, revisited, nest, affectInfo, parentRollbacker,
            allocatable->getHiddenTrueCheckConstraints(), &isSkipped, 
            !allocatable->isZone());
        if (hiddenIsPassed == false) {
          // Clear hiding state of Allocatable
          allocatable->setHiddenChecked(false);
        } else {
          LOG_arbitrateAreaLogLine(
              alloSymbol + "[" + alloName + "] change "
                  + allocatable->getHiddenSymbol());
        }
      }

      // -------------------------------------
      // For Zone, judge attenuation after hiding (mute)
      // -------------------------------------
      bool attenuateIsPassed {true};
      if (allocatable->isZone()) {
        RBAZoneImpl* const zone {dynamic_cast<RBAZoneImpl*>(allocatable)};
        // Mark "attenuattion" of target "Zone" as checked"
        zone->setAttenuateChecked(true);
        // Set "attenuattion" of target "Zone" to false
        zone->setAttenuated(false);
        LOG_arbitrateAreaLogLine(
            "  check online constraints to confirm zone attenuated state");
        attenuateIsPassed = checkConstraintAndReArbitrate(
            allocatable, revisited, nest, affectInfo, parentRollbacker,
            allocatable->getAttenuateFalseCheckConstraints(), &isSkipped, true);
        if (attenuateIsPassed == false) {
          zone->setAttenuated(true);
          attenuateIsPassed = checkConstraintAndReArbitrate(
              allocatable, revisited, nest, affectInfo, parentRollbacker,
              allocatable->getAttenuateTrueCheckConstraints(), &isSkipped, true);
          if (attenuateIsPassed == false) {
            allocatable->setAttenuateChecked(false);
          } else {
            LOG_arbitrateAreaLogLine(
                alloSymbol + "[" + alloName + "] change attenuated");
          }
        }
      }
#ifdef RBA_USE_LOG
      {
        std::string str = alloSymbol + "[" + alloName + "] ";
        if (allocatable->isArea() == true) {
          str += "displays";
        } else {
          str += "outputs";
        }
        str += " Content[";
        const RBAContentState* state = allocatable->getState();
        if (state == nullptr) {
          str += "null";
        } else {
          str += state->getOwner()->getElementName() + "::"
            + state->getElementName();
        }
        str += "] " + allocatable->getHiddenSymbol() + "["
            + RBALogManager::boolToString(allocatable->isHidden()) + "]";
        if (allocatable->isZone() == true) {
          str += " attenuated["
              + RBALogManager::boolToString(allocatable->isAttenuated()) + "]";
        }
        str += "\n";
        LOG_arbitrateAreaLogLine(str);
      }
#endif
      if ((hiddenIsPassed == true) && (attenuateIsPassed == true)) {
        break;
      }
    }
  }
  // ---------------------------------------------------------------------
  // Re-arbitration of the Allocatable　that influenced
  // ---------------------------------------------------------------------
  if ((beforeState != allocatable->getState())
          || allocatable->isHidden()
          || allocatable->isAttenuated()) {

    // Re-arbitration is performed in a state other than "hidden" 
    // When allocating content. Therefore, if state become "hidden" or 
    // "attenuation", re-arbitration is required for the "allocatable" 
    // that was affected by re-arbitration during content allocation.
    // Update the increased Area that influenced
    if (allocatable->isHidden() || allocatable->isAttenuated()) {
      for (const auto& a : allocatable->getAllocatablesAffectedByYou()) {
        static_cast<void>(affectAllocatables.insert(a));
      }
    }

    // If the re-arbitration source of Area/Zone (including any re-arbitration
    // sources, if any reconciliation nests) becomes an Area/Zone affected by 
    // the re-arbitration area/zone, such Area/Zone is excluded from 
    // the re-arbitration target and the affected Area/Zone is re-arbitrated.
    // Further, even if the affected Area/Zone is unarbitrated Allocatable
    // at that time, it is excluded from the re-arbitration target of 
    // the affected Area. This is because it is sufficient to arbitrate 
    // during normal arbitration. 
    for (const auto& a : revisited) {
      if (affectAllocatables.find(a) != affectAllocatables.end()
          || (!a->isChecked())) {
        static_cast<void>(affectAllocatables.erase(a));
      }
    }
    std::list<const RBAAllocatable*> sortedAllocatables(affectAllocatables.begin(),affectAllocatables.end());
    sortedAllocatables.sort(&RBAAllocatable::compareIndex);
    if (parentRollbacker != nullptr) {
      std::shared_ptr<RBARollbacker> rollbacker {std::make_shared<RBARollbacker>()};
      parentRollbacker->addChild(rollbacker);
      rollbacker->backup(sortedAllocatables);
    }

    for (auto& affect : sortedAllocatables) {
      // Remove Allocatable which will be re-arbitration from Allocatable 
      // that influenced Allocable during arbitration.
      allocatable->removeAffectAllocatable(affect);
    }
    static_cast<void>(revisited.insert(allocatable)); // Add to arbitrated Area
    for (auto& affectAllocatable : sortedAllocatables) {
      // @Deviation (EXP55-CPP,Rule-5_2_5,A5-2-3)
      // [Contents that deviate from the rules]
      //  This is a 'const_cast' expression that strips away a 'const' or 
      //  'volatile' qualifier.
      // [Why there is no problem if it deviate from the rules]
    　　//  Confirmed that there is no problem from the design point of view.
      //  We won't fix it now because we need to redesign the class, but
      //  no much effort as of now.
      RBAAllocatable* allo {const_cast<RBAAllocatable*>(affectAllocatable)};

      // Initialize the check flag of the Allocatable that performs the 
      // re-arbitration of the affetcted Allocatable
      // If the affected Allocables are cleared in advance, a skip occurred in 
      // the constraint expression evaluation during the re-arbitration of 
      // the affected Allocatable that was carried out earlier, after that 
      // re-arbitration will work during re-arbitration of affected Allocatable.
      // Therefore, clear check flag individually 
      // before re-arbitration of affected Allocable
      allo->clearChecked();

      LOG_arbitrateAreaLogLine( "    " +
          affectAllocatable->getSymbol() + "["
                                + affectAllocatable->getElementName()
                                + "] affect allocatable check start");
      // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
      // [Contents that deviate from the rules]
      //  Recursively calling arbitrateAllocatable()
      // [Why there is no problem if it deviate from the rules]
      //  - This process is necessary for re-arbitration of the affected Area, 
      //  - stack overflow will not occur becasue the infinite loop 
      //    prevention process is imeplemented.
      arbitrateAllocatable(allo, revisited, nest + 1, affectInfo,
                           parentRollbacker);
    }
    for(const RBAAllocatable* const revisitAllocatable : sortedAllocatables) {
      static_cast<void>(revisited.erase(revisitAllocatable));
    }
  }

  // --------------------------------------------------
  // Delete temporary affect information 
  // to prevent infinite loop during re-arbitration
  // --------------------------------------------------
  affectInfo->removeAffectInfo(allocatable);
#ifdef RBA_USE_LOG
  RBALogManager::setIndent(nest-1);
#endif
}

/**
 * @brief Sort content state based on arbitration policy
 * @param allocatable
 * @param contentStates
 * @return success/failure of sort
 */
bool
RBAArbitrator::
sortContentStates(const RBAAllocatable* const allocatable,
                  std::list<const RBAContentState*>& states) const
{
  bool isResult {true};
  switch(allocatable->getAllocatableArbitrationPolicy()) {
  case RBAArbitrationPolicy::FIRST_COME_FIRST:
	states.sort(&RBAContentState::compareFirstComeFirst);
    break;
  case RBAArbitrationPolicy::LAST_COME_FIRST:
	states.sort(&RBAContentState::compareLastComeFirst);
    break;
  case RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST:
	states.sort(&RBAContentState::comparePriorityFirstComeFirst);
    break;
  case RBAArbitrationPolicy::DEFAULT:
  case RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST:
	states.sort(&RBAContentState::comparePriorityLastComeFirst);
    break;
  default:
    isResult = false;
    break;
  }

  return isResult;
}

/**
 * @brief Get re-arbitration list from judgment NG constraint
 * @param totalRevisitAllocatables
 * @param allocatable
 * @param falseConstraints
 * @param revisited
 */
void
RBAArbitrator::
collectRevisitAllocatable(std::list<const RBAAllocatable*>* const totalRevisitAllocatables,
        RBAAllocatable*& allocatable,
        std::list<RBAConstraintImpl*>& falseConstraints,
        std::set<const RBAAllocatable*>& revisited)
{
  std::set<const RBAAllocatable*> revisitAllocatablesSet;

　　// Determine if re-arbitration should be done based on the constraint 
  // that the determination was NG
  for(RBAConstraintImpl*& constraint : falseConstraints) {
    // Get Contraint information
    const RBAConstraintInfo* const info {constraint->getInfo()};
    // Allocatable, a candidate for re-arbitration
    std::set<const RBAAllocatable*> rightFalseAllocatables;

    if (info->needsRearbitrationFor(allocatable)) {
      info->collectRearbitrationTargetFor(allocatable, rightFalseAllocatables, false);
    }
    if (rightFalseAllocatables.empty()) {
      // Non-implication constraint　expression
      // To ensure that "currently arbitrated allocable" does not lose to lower 
      // priority allocable, arbitration of low priority Allocable is performed 
      // if low priority Allocable is included in 
      // "re-arbitration candidate Allocable".
      info->collectFalseAllocatables(rightFalseAllocatables);
      bool isContainsLowPriorityAllocatable {false};
      for(const RBAAllocatable* const rightFalseAllocatable
	    : rightFalseAllocatables) {
        if(RBAAllocatable::compareIndex(allocatable,rightFalseAllocatable)) { 
        // index is smaller for higher priority allocable
          isContainsLowPriorityAllocatable = true;
          break;
        }
      }
      if(!isContainsLowPriorityAllocatable) {
        continue;
      }
    }

    // Remove Allocable during arbitration from re-arbitration target
    static_cast<void>(rightFalseAllocatables.erase(allocatable));

    // If even one Allocable candidate for re-arbitration has been 
    // re-arbitrated, re-arbitration will not be performed again.
    // Go to next content assignment
    for(const RBAAllocatable* const rightFalseAllocatable : rightFalseAllocatables) {
      if(revisited.find(rightFalseAllocatable) != revisited.end()) {
        return;
      }
    }

    // Set re-arbitration Allocable
    for(const RBAAllocatable* const alloc : rightFalseAllocatables) {
      static_cast<void>(revisitAllocatablesSet.insert(alloc));
    }
  }

  // Re-arbitration Allocatable exists
  if(!(revisitAllocatablesSet.empty())) {
    // copy std::set to std::list 
    static_cast<void>(totalRevisitAllocatables->insert(totalRevisitAllocatables->end(), 
                      revisitAllocatablesSet.begin(), 
                      revisitAllocatablesSet.end()));
    // Sort re-arbitration Areas in ascending order based on priority
    // It is necessary to sort by index comparison considering the order of models.
    totalRevisitAllocatables->sort(&RBAAllocatable::compareIndex);
  }
}

/**
 * Confirm cancellation of all content status 
 * to cancel Request which lost in arbitration
 */
void
RBAArbitrator::
postArbitrate()
{
#ifdef RBA_USE_LOG
  RBALogManager::cancelRequestLogLine("----Cancel Request----");
#endif
  for(const RBAContentState* const state : model_->getContentStates()) {
#ifdef RBA_USE_LOG
    RBALogManager::cancelRequestLogLine("Content["+
			     state->getOwner()->getElementName()+"::"+
			     state->getElementName()+
			     "] check start");
#endif
    static_cast<void>(cancelChecked_.insert(state));
    if(!result_->isActive(state)) {
#ifdef RBA_USE_LOG
	    RBALogManager::cancelRequestLogLine("  Content["+
				 state->getOwner()->getElementName()+"::"+
				 state->getElementName()+
				 "] is not Active skip");
#endif
      continue;
    }
    if(result_->isAlreadyOutputting(state)) {
#ifdef RBA_USE_LOG
      std::string contTypeName;
      if(state->isViewContentState()) {
        contTypeName = "Visible";
      }
      else {
        contTypeName = "Sounding";
      }
      RBALogManager::cancelRequestLogLine("  Content["+
                                          state->getOwner()->getElementName()+"::"+
                                          state->getElementName()+
                                          "] is "+contTypeName+" skip");
#endif
      continue;
    }

    changeContentStateCancelWithPolicy(state);
  }

#ifdef RBA_USE_LOG
  // Log output for coverage of request cancellation
  for(const RBAContentState* state : model_->getContentStates()) {
    std::string contentName = state->getOwner()->getElementName();
    std::string stateName = state->getElementName();
    std::string canceled = isCancel(state) ? "t" : "f";
    RBALogManager::coverageCanceledRequestLogLine(
        contentName + "," + stateName + ',' +canceled);
  }
#endif
}

/**
 * @brief Change the cancellation information of hidden Content status 
          based on arbitration results and cancellation policy
 * @param state
 */
void
RBAArbitrator::
changeContentStateCancelWithPolicy(const RBAContentState* const state)
{
  switch(dynamic_cast<RBAContent*>(state->getOwner())->getContentLoserType()) {
  case RBAContentLoserType::GOOD_LOSER:
#ifdef RBA_USE_LOG
     RBALogManager::cancelRequestLogLine("  Content["+
                              state->getOwner()->getElementName()+"::"+
                              state->getElementName()+
                              "] is Canceled because GOOD_LOSER");
#endif
    setCancel(state, true);
    break;
  case RBAContentLoserType::NEVER_GIVEUP:
#ifdef RBA_USE_LOG
    RBALogManager::cancelRequestLogLine("  Content["+
                             state->getOwner()->getElementName()+"::"+
                             state->getElementName()+
                             "] is not Canceled because NEVER_GIVEUP");
#endif
    setCancel(state, false);
    break;
  case RBAContentLoserType::DO_NOT_GIVEUP_UNTIL_WIN:
    if(state->isModelElementType(RBAModelElementType::ViewContentState)) {
      if(result_->isPreVisible(dynamic_cast<const RBAViewContentStateImpl*>(state))) {
#ifdef RBA_USE_LOG
        RBALogManager::cancelRequestLogLine("  Content["+
                                 state->getOwner()->getElementName()+"::"+
                                 state->getElementName()+
                                 "] is Canceled because DO_NOT_GIVEUP_UNTIL_WIN");
#endif
        setCancel(state, true);
      } else {
#ifdef RBA_USE_LOG
        RBALogManager::cancelRequestLogLine("  Content["+
                                 state->getOwner()->getElementName()+"::"+
                                 state->getElementName()+
                                 "] is not Canceled because DO_NOT_GIVEUP_UNTIL_WIN");
#endif
        setCancel(state, false);
      }
    }
    else {
      if(result_->isPreSounding(dynamic_cast<const RBASoundContentStateImpl*>(state))) {
        setCancel(state, true);
      } else {
        setCancel(state, false);
      }
    }
    break;
  default:
    break;
  }
}

#ifdef RBA_USE_LOG
void
RBAArbitrator::
checkAllConstraints()
{
  std::string log;
  LOG_arbitrateConstraintLogLine("----Check All Constraint----");

  if(simulationMode_) {
    for(const RBAConstraintImpl* constraint : model_->getConstraintImpls()) {
      bool result = const_cast<RBAConstraintImpl*>(constraint)->execute(this);
      if(result == false) {
	result_->addFailedConstraint(constraint);
      }
      if (constraint->isRuntime() == true) {
        log += "online  ";
      } else {
        log += "offline ";
      }
      log += "constraint[" + constraint->getElementName() + "] ";
      log += "result[" + RBALogManager::boolToString(result) + "]\n";
    }
    if (log.empty() != true ) {
      log.erase(log.end() - 1, log.end()); // Remove last line break
    }
  }

}
#endif

void
RBAArbitrator::
checkCancelContent() const
{
  for(const RBAViewContentState* const viewState
	: result_->getActiveViewContentStates()) {
    if(result_->isCancel(viewState)) {
      result_->cancelContentState(dynamic_cast<const RBAContentState*>(viewState));
    }
  }
  for(const RBASoundContentState* const soundState
	: result_->getActiveSoundContentStates()) {
    if(result_->isCancel(soundState)) {
      result_->cancelContentState(dynamic_cast<const RBAContentState*>(soundState));
    }
  }
}

/**
 * @brief Update display and non-dislay Allocatable List
 */
void
RBAArbitrator::
updateResult()
{
  // Deactivate canceled Content
  result_->updateActiveContentStates();

  // Update coordinates　of Area 
  for(auto& area : result_->getVisibleAreas()) {
    const RBAAreaImpl* const areaImpl {dynamic_cast<const RBAAreaImpl*>(area)};
    const auto posCont = model_->findPositionContainerImpl(area->getName());
    const auto sizeObj = result_->getSize(area);
    if((posCont != nullptr) && (sizeObj != nullptr)) {
      const auto offset = posCont->getOffset(sizeObj->getName());
      const_cast<RBAAreaImpl*>(areaImpl)->setOffsetX(offset.first);
      const_cast<RBAAreaImpl*>(areaImpl)->setOffsetY(offset.second);
    }
  }

  // Set output Content state list
  std::set<const RBAContentState*> outputtingContentStateSet;
  for(auto& alloc : result_->getOutputtingAllocatables()) {
    const auto state = result_->getAllocatedContentState(alloc);
    static_cast<void>(outputtingContentStateSet.insert(state));
  }
  for(auto& state : outputtingContentStateSet) {
    static_cast<void>(result_->addOutputtingContentState(state));
  }
  
  for(auto& state : result_->getActiveContentStates()) {
    // If the Area allocated in the display request is not displayed, 
    // set it to "Stanby Content".
    const auto allocs = result_->getAllocatable(state);
    if(allocs.empty()) {
      result_->addStandbyContent(dynamic_cast<RBAContent*>(state->getOwner()));
    }
  }
}

/**
 * ### Generate result information
 *
 * Generate animation information (RBAViewAction) and register it in the 
 * viewActions list of RBAResult.
 * The animation information generation pattern is as follows.
 * | Area A(pre)  | Area B(pre) | Area A(cur)  | Area B(cur) | type               |
 * |:-:           |:-:          |:-:           |:-:          |:----               |
 * | (none)       | -           | **content**  | -           | TRANSITON_ADD      |
 * | **content**  | -           | (none)       | -           | TRANSITION_REMOVE  |
 * | **contentA** | -           | **contentB** | -           | TRANSITION_REPLACE |
 * | **content**  | (none)      | (none)       | **content** | MOVE               |
 */
void
RBAArbitrator::
createResultData()
{
  std::list<std::unique_ptr<RBAViewAction>> actions;
  // Check the Areas that have not changed
  std::set<const RBAArea*> stableAreas;
  for(const RBAArea* const preArea : result_->getPreVisibleAreas()) {
    if(result_->isVisible(preArea)) {
      const RBAViewContent* const curContent {result_->getContentState(preArea)->getOwner()};
      const RBAViewContent* const preContent {result_->getPreContentState(preArea)->getOwner()};
      if(curContent == preContent) {
        static_cast<void>(stableAreas.insert(preArea));
      }
    }
  }
  // Check "MOVE"
  std::set<const RBAViewContent*> movedContents;
  for(const RBAArea* curArea : result_->getVisibleAreas()) {
    // Current display Area
    const RBAViewContentState* curState {result_->getContentState(curArea)};
    const RBAViewContent* const curContent {curState->getOwner()};
    // Skip stable Area
    if(stableAreas.find(curArea) != stableAreas.end()) {
      continue;
    }
    for(const RBAArea* preArea : result_->getPreVisibleAreas()) {
      // Do not consider stable areas to have changed
      if (stableAreas.find(preArea) != stableAreas.end()) {
    	  continue;
      }
      // Previous display Area
      const RBAViewContent* const preContent {result_->getPreContentState(preArea)->getOwner()};
      if(curContent == preContent) {
        // "MOVE" if there is matching content
        actions.push_back(std::make_unique<RBAViewMove>(preArea, curArea,
							curState));
        // Check moved Content
        static_cast<void>(movedContents.insert(curState->getOwner()));
      }
    }
  }
  // Check "REMOVE"
  for(const RBAArea* preArea : result_->getPreVisibleAreas()) {
    // Skip  stable Area
    if(stableAreas.find(preArea) != stableAreas.end()) {
      continue;
    }
    const RBAViewContentState* preState {result_->getPreContentState(preArea)};
    // Skip if Content is "MOVE"
    if(movedContents.find(preState->getOwner())
       != movedContents.end()) {
      continue;
    }
    if(!result_->isVisible(preArea)) {
      // If the previously displayed Area isn't displayed, it is REMOVE.
      actions.push_back(std::make_unique<RBAViewTransition>(
          RBAViewActionType::TRANSITION_REMOVE, preArea, preState));
    }
  }
  // Check Examine ADD/REMOVE and REPLACE related to MOVE
  for(const RBAArea* curArea : result_->getVisibleAreas()) {
    // Display Area at this time
    // Skip stable Area
    if(stableAreas.find(curArea) != stableAreas.end()) {
      continue;
    }
    const RBAViewContentState* curState {result_->getContentState(curArea)};
    const RBAViewContent* const curContent {curState->getOwner()};
    const RBAViewContentState* preState {result_->getPreContentState(curArea)};
    
    if(movedContents.find(curContent) != movedContents.end()) {
      if((preState != nullptr) && (!result_->isVisible(preState))) {
        // If the previously displayed content isn't displayed, it is REMOVE.
        actions.push_back(std::make_unique<RBAViewTransition>(
			  RBAViewActionType::TRANSITION_REMOVE,
			  curArea, preState));
      }
      else {
	continue;
      }
    }
    else if(result_->isPreVisible(curArea)) {
      // It was the display Area last time
      // If pre is MOVE content
      const RBAViewContent* const preContent {preState->getOwner()};
      if(movedContents.find(preContent) != movedContents.end()) {
        // Content at this time is ADD
        actions.push_back(std::make_unique<RBAViewTransition>(
		          RBAViewActionType::TRANSITION_ADD,
			  curArea, curState));
      }
      else if(curContent != preContent) {
        // REPLACE because the content is different
        actions.push_back(std::make_unique<RBAViewTransition>(
			  RBAViewActionType::TRANSITION_REPLACE,
			  curArea, preState, curState));
      } else {
        ;
      }
    }
    else {
      // ADD because it was not the display Area last time
      actions.push_back(std::make_unique<RBAViewTransition>(
			RBAViewActionType::TRANSITION_ADD,
			curArea, curState));
    }
  }

  // Sort and register
  actions.sort(&compareViewAction);
  for(auto& action : actions) {
    result_->addViewAction(action);
  }
}

void
RBAArbitrator::differenceArbitrate()
{
#ifdef RBA_USE_LOG
  // Set request information in log
  RBALogManager::setType(RBALogManager::TYPE_REQUEST);
  logRequestArbitration();
  RBALogManager::setType(RBALogManager::TYPE_PREVIOUS_RESULT);
  logPreResultArbitration();
  logRequestForCoverage();
#endif

  for (auto& a : model_->getSortedAllocatables()) {
    a->clearStatus();
  }

  // ----------------------------------------------------------
  // Arbitration
  // ----------------------------------------------------------
  // Priority and post-win arbitoration
  // (Value arbitration is the same as priority arbitration)
#ifdef RBA_USE_LOG
RBALogManager::setType(RBALogManager::TYPE_ARBITRATE);
#endif
  arbitrate(model_->getSortedAllocatables());

  // ----------------------------------------------------------
  // Post processing of arbitration
  // ----------------------------------------------------------
#ifdef RBA_USE_LOG
RBALogManager::setType(RBALogManager::TYPE_CANCEL_REQUEST);
#endif
  // when the constraint expression is evaluated by satisfiesConstraints(),
  // if the cancel state is different from the time when execute() is executed, 
  // the result may be false. Therefore, it is necessary to store 
  // the state before cancellation processing.
  // When performing the constraint expression evaluation in 
  // satisfiedConstraints(), restore to this value and evaluate.
  resultSetForSatisfiesConstraints_ = std::make_unique<RBAResultSet>(
      *result_->getCurResultSet());
  postArbitrate();

  // Move offline Constraint
#ifdef RBA_USE_LOG
RBALogManager::setType(RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS);
  checkAllConstraints();
#endif

  // ----------------------------------------------------------
  // Update Content state
  // ----------------------------------------------------------
  for (auto& c : model_->getContents()){
    const_cast<RBAContent*>(c)->updateStatus(result_.get());
  }

  backupResultSet_ = result_->createBackupCurrentResultSet();
  nextResultSet_ = result_->createNextCurrentResultSet();

#ifdef RBA_USE_LOG
  logResultForCoverage();
#endif
}

bool
RBAArbitrator::
checkConstraints( std::list<RBAConstraintImpl*>& constraints,
                  std::list<RBAConstraintImpl*>& falseConstraints,
                  const RBAAllocatable* const allocatable)
{
  bool containsSkip {false};
  for (const auto& constraint : constraints) {
    const bool isPassed {constraint->execute(this)};
    if (isPassed == false) {
      falseConstraints.push_back(constraint);
    }
    if (constraint->getInfo()->isExceptionBeforeArbitrate()) {
      if (constraint->getInfo()->needsReRearbitrationFor(allocatable)) {
        containsSkip = true;
      }
    }
  }
  return containsSkip;
}

bool
RBAArbitrator::
checkConstraintAndReArbitrate(RBAAllocatable* allocatable,
                              std::set<const RBAAllocatable*>& revisited,
                              const std::int32_t nest,
                              RBAAffectInfo* const affectInfo,
                              RBARollbacker* const parentRollbacker,
                              std::list<RBAConstraintImpl*>& constraints,
                              bool * const isSkipped,
                              const bool isFinal)
{
  bool isPassed {false};
  std::list<RBAConstraintImpl*> falseConstraints;
  const bool containsSkip {checkConstraints(constraints, falseConstraints, allocatable)};
  if(falseConstraints.empty()) {
    *isSkipped = (*isSkipped || containsSkip);
    if(!containsSkip && !*isSkipped && isFinal) {
      static_cast<void>(revisited.insert(allocatable));
    }
    isPassed = true;
  } else {
    std::list<const RBAAllocatable*> revisitAllocatables;
    collectRevisitAllocatable(&revisitAllocatables, allocatable, falseConstraints, revisited);
    if(!(revisitAllocatables.empty())) {
      // There is re-arbitration Allocatable.
      // Generates backup information for rollback when re-arbitration fails.
      // For efficiency, instantiate only once when re-arbitration is needed 
      // for the first time.
      // Since it is backed up after content allocation, 
      // it is necessary to set NULL to the allocated content after rollback.

      // Rollback information when arbitration fails
      std::shared_ptr<RBARollbacker> rollbacker {std::make_shared<RBARollbacker>()}; 
      if (parentRollbacker != nullptr) {
        parentRollbacker->addChild(rollbacker);
      }
      rollbacker->backup(revisitAllocatables);
      // Initialize all re-arbitration Allocatable
      for (auto& a : revisitAllocatables) {
        const_cast<RBAAllocatable*>(a)->clearChecked();
      }
      // --------------------------------------------------
      // Re-arbitrate "Allocatable" that has not been re-arbitrated 
      // in the re-arbitration candidate list
      // --------------------------------------------------
      static_cast<void>(revisited.insert(allocatable));
      for(const RBAAllocatable* const revisitAllocatable : revisitAllocatables) {
        LOG_arbitrateAreaLogLine( "    " +
            revisitAllocatable->getSymbol() + "["
                                  + revisitAllocatable->getElementName()
                                  + "] revisit allocatable check start");
        arbitrateAllocatable(const_cast<RBAAllocatable*>(revisitAllocatable),
			     revisited, nest + 1, affectInfo, rollbacker.get());
      }
      for(const RBAAllocatable* const revisitAllocatable : revisitAllocatables) {
        static_cast<void>(revisited.erase(revisitAllocatable));
      }
      // --------------------------------------------------
      // Check if content allocation succeeded as a result of re-arbitration
      // --------------------------------------------------
      falseConstraints.clear();
      static_cast<void>(checkConstraints(constraints, falseConstraints, allocatable));
      if (falseConstraints.empty()) {
        // The content of the allocatable allocation is fixed by re-arbitration,
        // so exit the loop and proceed to the next allocatable.
        // In some cases, "Allocatable" is re-arbitrated due to recursion and 
        // allocated Content is lost, but go to the next Allocable because
        // all contents have been checked
        isPassed = true;
      } else {
        // Roll back arbitration status and affected information
        rollbacker->rollback(); 
        if (parentRollbacker != nullptr) {
          parentRollbacker->removeChild(rollbacker);
        }
      }
    }
  }
  if (isPassed == false) {
    //Collect Areas that affected the area in arbitration status
    std::set<const RBAAllocatable*> allocatablesWhichHaveAffectedToThisAllocatable;

    for (const RBAConstraintImpl* const constraint : falseConstraints) {
      constraint->getInfo()->collectAffectedAllocatables(
          false, allocatablesWhichHaveAffectedToThisAllocatable, false,
          false);
    }
    static_cast<void>(allocatablesWhichHaveAffectedToThisAllocatable.erase(allocatable));

    // Record fact that affected the area being arbitrated on Area that 
    // affected Area during arbitration.
    // The re-arbitration of the affected area is recorded in AffectInfo, 
    // so it does not record the re-arbitrated area.
    for (const RBAAllocatable* const a : allocatablesWhichHaveAffectedToThisAllocatable) {
      if (!(affectInfo->alreadyKnowsThatFormerHasAffectedToLatter(a,
                                                                  allocatable))) {
        const_cast<RBAAllocatable*>(a)->addAllocatableWhichHasBeenAffectedByYou(
            allocatable);
        affectInfo->addInfoThatFormerAffectedToLatter(a, allocatable);
      }
    }
  }
  return isPassed;
}

void
RBAArbitrator::
setCancel(const RBAContentState* const state, const bool checked)
{
  result_->setCancel(state, checked);
}

bool
RBAArbitrator::
isCancel(const RBAContentState* const state) const
{
  if(state->isViewContentState()) {
    return result_->isCancel(state);
  }
  else {
    return result_->isCancel(state);
  }
}

void
RBAArbitrator::
getSortedContentStates(const RBAAllocatable* const allocatable,
                       std::list<const RBAContentState*>& contentStates) const
{
  for (const RBAContent* const content : allocatable->getInternalContents()) {
    const RBAContentState* const state {result_->getActiveState(content)};
    if (state != nullptr) {
      contentStates.push_back(state);
#ifdef RBA_USE_LOG
    } else {
      RBALogManager::arbitrateContentLogLine(
          "  Content[" + content->getElementName() + "] is not Active skip");
#endif
    }
  }
  static_cast<void>(sortContentStates(allocatable, contentStates));
  // Add null at the end, to evaluate constraint expression when unassigned
  contentStates.push_back(nullptr);
}

std::int32_t
RBAArbitrator::
getViewActionPriority(const RBAViewActionType viewActionType)
{
  std::int32_t result{0};

  switch(viewActionType) {
  case RBAViewActionType::TRANSITION_REMOVE:
    result = 4;
    break;
  case RBAViewActionType::MOVE:
    result = 3;
    break;
  case RBAViewActionType::TRANSITION_ADD:
    result = 2;
    break;
  case RBAViewActionType::TRANSITION_REPLACE:
    result = 1;
    break;
  default:
    break;
  }

  return result;
}

bool
RBAArbitrator::
compareViewAction(const std::unique_ptr<RBAViewAction>& lhs,
                  const std::unique_ptr<RBAViewAction>& rhs)
{
  const std::int32_t lval {getViewActionPriority(lhs->getViewActionType())};
  const std::int32_t rval {getViewActionPriority(rhs->getViewActionType())};

  return lval > rval;
}

RBAResultImpl*
RBAArbitrator::getResult() const
{
  return result_.get();
}

void RBAArbitrator::setResult(std::unique_ptr<RBAResultImpl> result)
{
  result_ = std::move(result);
}

std::set<const RBAContentState*>& RBAArbitrator::getCancelChecked()
{
  return cancelChecked_;
}

std::unique_ptr<RBAResultImpl>& RBAArbitrator::getResultRef() const
{
  return result_;
}

std::unique_ptr<RBAResultSet>& RBAArbitrator::getNextResultSet()
{
  return nextResultSet_;
}

void RBAArbitrator::setNextResultSet(std::unique_ptr<RBAResultSet> nextResultSet)
{
  nextResultSet_ = std::move(nextResultSet);
}

std::unique_ptr<RBAResultSet>& RBAArbitrator::getBackupResultSet()
{
  return backupResultSet_;
}

void RBAArbitrator::setBackupResultSet(std::unique_ptr<RBAResultSet> backupResultSet)
{
  backupResultSet_ = std::move(backupResultSet);
}

std::unique_ptr<RBAResultSet>& RBAArbitrator::getReservedResultSet()
{
  return reservedResultSet_;
}

void RBAArbitrator::setReservedResultSet(std::unique_ptr<RBAResultSet> reservedResultSet)
{
  reservedResultSet_ = std::move(reservedResultSet);
}

std::recursive_mutex& RBAArbitrator::getMutex() const
{
  return mutex_;
}

#ifdef RBA_USE_LOG
void RBAArbitrator::setSimulationMode(bool simulationMode)
{
  simulationMode_ = simulationMode;
}
#endif

std::deque<std::unique_ptr<RBARequestQueMember>>& RBAArbitrator::getRequestQue()
{
  return requestQue_;
}

#ifdef RBA_USE_LOG
/**
 * Output request information for log view
 */
void
RBAArbitrator::logRequestArbitration()
{
  const std::list<const RBAAllocatable*> allocatables =
      model_->getAllocatables();
  RBALogManager::requestLogLine("----Request Information----");
  RBALogManager::requestLogLine(
      "Allocatable Count:" + std::to_string(allocatables.size()));
  for (const RBAAllocatable* allocatable : allocatables) {
    RBALogManager::requestLogLine(
        "  " + allocatable->getSymbol() + "[" + allocatable->getElementName()
            + "] policy[" + allocatable->getArbitrationPolicyString()
            + "] visibility[" + allocatable->getVisibilityString() + "]");
  }

  const std::list<const RBAContentState*> contentStates = model_
      ->getContentStates();
  RBALogManager::requestLogLine(
      "ContentState Count:" + std::to_string(contentStates.size()));
  for (const RBAContentState* contentState : contentStates) {
    std::string active;
    if (contentState->getModelElementType() == RBAModelElementType::ViewContentState) {
      active = RBALogManager::boolToString(
          result_->isActive(
              dynamic_cast<const RBAViewContentState*>(contentState)));
    } else {
      active = RBALogManager::boolToString(
          result_->isActive(
              dynamic_cast<const RBASoundContentState*>(contentState)));
    }
    RBALogManager::requestLogLine(
        "  " + dynamic_cast<RBAContent*>(contentState->getOwner())->getSymbol() + "["
            + contentState->getOwner()->getElementName() + "::"
            + contentState->getElementName() + "] priority["
            + contentState->getPriorityString() + "] isActive[" + active
            + "] order[" + contentState->getOrderString() + "]");
  }

  const std::list<const RBAScene*> scenes = model_->getScenes();
  RBALogManager::requestLogLine("Scene Count:" + std::to_string(scenes.size()));
  for (const RBAScene* scene : scenes) {
    RBALogManager::requestLogLine(
        "  Scene[" + scene->getName() + "] isActive["
            + RBALogManager::boolToString(result_->isActive(scene))
            + "]");
  }

  std::list<RBAConstraint*> constraints = model_->getConstraints();
  RBALogManager::requestLogLine(
      "Constraint Count:" + std::to_string(constraints.size()));
  for (RBAConstraint* constraint : constraints) {
    RBAConstraintImpl* impl = dynamic_cast<RBAConstraintImpl*>(constraint);
    RBALogManager::requestLogLine(
        "  Constraint[" + impl->getName() + "] Expression["
            + impl->getExpression()->getExpressionText() + "] runtime["
            + RBALogManager::boolToString(impl->isRuntime()) + "]");
  }

}

/**
 * Output previous arbitration result for log view
 */
void
RBAArbitrator::logPreResultArbitration()
{
  RBALogManager::resultLogLine("----Previous Result Information----");

  auto allocs = model_->getAllocatables();
  RBALogManager::resultLogLine("Allocatable TotalCount:"
                               + std::to_string(allocs.size()));
  for (auto& alloc : allocs) {
    auto contentState = result_->getPreContentState(alloc);
    auto hidden = result_->isPreHidden(alloc);
    std::string str = "  " + alloc->getSymbol()
                      + "[" + alloc->getElementName() + "] Content[";
    if (contentState == nullptr) {
      str += "null";
    } else {
      str += contentState->getOwner()->getElementName()
             + "::" + contentState->getElementName();
    }
    str += "] " + alloc->getHiddenSymbol()
           + "[" + RBALogManager::boolToString(hidden) + "]";
    if (alloc->isZone() == true) {
      str += " attenuated[";
      str += RBALogManager::boolToString(
              result_->isPreAttenuated(dynamic_cast<const RBAZone*>(alloc)));
      str += "]";
    }
    RBALogManager::resultLogLine(str);
    if (contentState && !hidden) {
      RBALogManager::coveragePrevResultLogLine(
        "A," + alloc->getElementName() + ","
        + contentState->getOwner()->getElementName() + ","
        + contentState->getElementName());
    }
  }

  auto contents = model_->getContents();
  RBALogManager::resultLogLine("Content TotalCount:"
                               + std::to_string(contents.size()));
  for (auto& content : contents) {
    auto state = result_->getPreActiveState(content);
    bool isOutputting = false;
    bool isActive = false;
    if (state != nullptr) {
      isActive = true;
      isOutputting = result_->isPreOutputting(state);
    }
    RBALogManager::resultLogLine(
      "  " + content->getSymbol() + "[" + content->getElementName() + "] "
      + content->getVisibleSymbol() + "["
      + RBALogManager::boolToString(isOutputting) + "] active["
      + RBALogManager::boolToString(isActive) + "]");
    for (auto alloc : content->getAllocatables()) {
      auto allocatedState = result_->getPreContentState(alloc);
      if ((allocatedState != nullptr)
          && (allocatedState->getOwner() == content)) {
        RBALogManager::resultLogLine(
          "    allocated " + alloc->getSymbol() + "["
          + alloc->getElementName() + "]");
      }
    }
  }
}

/**
 * Output current arbitration result for log view
 */
void
RBAArbitrator::logResultArbitration()
{
  RBALogManager::resultLogLine("----Result Information----");

  const std::list<const RBAAllocatable*> allocatables
    = model_->getAllocatables();
  RBALogManager::resultLogLine("Allocatable TotalCount:" + std::to_string(allocatables.size()));
  for(const RBAAllocatable* allocatable : allocatables) {
    const RBAContentState* contentState = result_->getContentState(allocatable);
    std::string str = "  ";
    str += allocatable->getSymbol();
    str += "[";
    str += allocatable->getElementName();
    str += "] Content[";
    if (contentState == nullptr) {
      str += "null";
    } else {
      str += contentState->getOwner()->getElementName() + "::"
        + contentState->getElementName();
    }
    str += "] ";
    str += allocatable->getHiddenSymbol();
    str += "[";
    str += RBALogManager::boolToString(result_->isHidden(allocatable));
    str += "]";
    if (allocatable->isZone() == true) {
      str += " attenuated[";
      str += RBALogManager::boolToString(result_->isAttenuated(dynamic_cast<const RBAZone*>(allocatable)));
      str += "]";
    }
    RBALogManager::resultLogLine(str);
  }

  const std::list<const RBAContent*> contents = model_->getContents();
  RBALogManager::resultLogLine("Content TotalCount:" + std::to_string(contents.size()));
  for(const RBAContent* content : contents) {
    bool isOutputting = false;
    bool isCancel = false;
    const RBAContentState* state = result_->getActiveState(content);
    if(state != nullptr) {
      isOutputting = result_->isOutputting(state);
    } else {
      for(const RBAContentState* state : content->getStates()) {
        isCancel |= result_->isCancel(state);
      }
    }
    RBALogManager::resultLogLine("  "
        + content->getSymbol()
        + "["
        + content->getElementName()
        + "] "
        + content->getVisibleSymbol()
        + "["
        + RBALogManager::boolToString(isOutputting)
        + "] cancel["
        + RBALogManager::boolToString(isCancel)
        + "]");
    for(const RBAAllocatable* allocatable : content->getAllocatables()) {
      const RBAContentState* allocatedState
	= result_->getContentState(allocatable);
      if((allocatedState != nullptr) && (allocatedState->getOwner() == content)) {
        RBALogManager::resultLogLine("    allocated "
                                     + allocatable->getSymbol() + "["
                                     + allocatable->getElementName() + "]");
      }
    }
  }
}

/**
 * For coverage: Output request information
 */
void
RBAArbitrator::logRequestForCoverage()
{
  for(const RBAContentState* contentState : model_->getContentStates()) {
    std::ostringstream oss;
    oss << "C,";
    if(result_->isActive(contentState)) {
      oss << "on,";
    }
    else {
      oss << "off,";
    }
    oss << contentState->getOwner()->getElementName() << ",";
    oss << contentState->getElementName() << ",";
    oss << contentState->getContentStateOrder();
    RBALogManager::coverageRequestLogLine(oss.str());
  }
  for(const RBAScene* scene : model_->getScenes()) {
    std::ostringstream oss;
    oss << "S,";
    if(result_->isActive(scene)) {
      oss << "on,";
    }
    else {
      oss << "off,";
    }
    oss << scene->getName();
    for(const auto& name : scene->getPropertyNames()) {
      std::int32_t value {result_->getSceneProperty(scene, name)};
      oss << ",";
      oss << name;
      oss << ":";
      oss << value;
    }
    RBALogManager::coverageRequestLogLine(oss.str());
  }
}

/**
 * For coverage: Output result information
 */
void
RBAArbitrator::logResultForCoverage()
{
  for(const RBAAllocatable* allocatable : model_->getAllocatables()) {
    std::ostringstream oss;
    oss << "A,";
    oss << allocatable->getElementName() + ",";
    const RBAContentState* contentState = result_->getContentState(allocatable);
    if((contentState != nullptr) && (!result_->isHidden(allocatable))) {
      oss << contentState->getOwner()->getElementName();
    }
    RBALogManager::coverageResultLogLine(oss.str());
  }
}

void
RBAArbitrator::setLogToResult()
{
  std::ostringstream oss;
  oss << RBALogManager::getAllConstraintLog();
  oss << RBALogManager::getRequestLog();
  oss << RBALogManager::getPreviousResultLog();
  oss << RBALogManager::getArbitrateLog();
  oss << RBALogManager::getCancelRequestLog();
  oss << RBALogManager::getCheckAllConstraintLog();
  oss << RBALogManager::getResultLog();
  result_->setLog(oss.str());
}
#endif

}
