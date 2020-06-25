// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA729_hierarchy.cpp
 */

#include <fstream>
#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "HA729_hierarchy.hpp"
#include "TestCommon.hpp"

namespace {
#ifdef RBA_USE_LOG
/*
 * BaseLogCollector
 */

BaseLogCollector::BaseLogCollector() {}
BaseLogCollector::~BaseLogCollector() {}

bool BaseLogCollector::open(std::string file_path)
{
  model_path = file_path;
  ofs.open(model_path, std::ofstream::out | std::ofstream::trunc); // open to overwrite
  if (ofs) {
    return true;
  }
  else {
    return false;
  }
}

void BaseLogCollector::write(std::string outputLine)
{
  if (ofs) {
    ofs << outputLine << std::endl;
  }
}

void BaseLogCollector::close()
{
  if (ofs) {
    ofs.close();
  }
}

bool BaseLogCollector::startsWith(const std::string &target,
                                  const std::string &keyword)
{
  if(target.size() >= keyword.size() &&
     std::equal(std::begin(keyword), std::end(keyword), std::begin(target))) {
    return true;
  }
  return false;
}

std::list<std::string>
BaseLogCollector::split(const std::string& line, const char sep)
{
  std::list<std::string> res;
  std::stringstream ss(line);
  std::string buf;
  while (std::getline(ss, buf, sep)) {
    res.push_back(buf);
  }

  return res;
}

/*
 * ConstraintLogCollector
 */
static const char SEPARATOR = ',';
static const char EXP_SEP = '\t';

ConstraintLogCollector::ConstraintLogCollector() {}
ConstraintLogCollector::~ConstraintLogCollector() {}

void ConstraintLogCollector::log(const std::string& log)
{
  if (startsWith(log, std::string("#HierarchyOfConstraint#DEF_START"))) {
    write("#DEF_START");
    defValid = true;
    expValid = false;
  }
  else if (startsWith(log, std::string("#HierarchyOfConstraint#DEF_END"))) {
    write("#DEF_END");
    defValid = false;
    expValid = false;
  }
  else if (defValid) {
    if (startsWith(log, "#HierarchyOfConstraint#START")) {
      std::list<std::string> strName = split(log, SEPARATOR); // "#Hiera...#START", "ModelName,ModelType" // ModelType: (Constraint, PostConstraint, Rule)
      std::list<std::string>::iterator strTCLog_itr = strName.begin();
      strTCLog_itr++; // "#Hiera...#START"
      strHeadString = *(strTCLog_itr++);
      strRuntime = *(strTCLog_itr++);
      strType = *(strTCLog_itr++);
      expValid = strRuntime.compare("t") == 0 ? true : false;
    } else if (startsWith(log, "#HierarchyOfConstraint#EXPRESSION")) {
      if (expValid) {
        std::list<std::string> strContents = split(log, EXP_SEP); // #Hie...#EXPRESSION", "<hierarchy>", "<expressionText>", "<expressionType>"
        std::list<std::string>::iterator itr = strContents.begin();
        std::string garbage(*(itr++));
        std::string hierarchy(*(itr++));
        std::string expressionText(*(itr++));
        if (strContents.size() == 3) {
          write(strHeadString + EXP_SEP + hierarchy + EXP_SEP + expressionText + EXP_SEP + strType);
        } else if (strContents.size() == 4) {
          std::string expressionType(*itr);
          write(strHeadString + EXP_SEP + hierarchy + EXP_SEP + expressionText + EXP_SEP + expressionType + EXP_SEP + strType);
        } else if (strContents.size() > 4) {
          int index = log.find(hierarchy) + hierarchy.length() + 1;
          write(strHeadString + EXP_SEP + hierarchy + EXP_SEP + log.substr(index) + EXP_SEP + strType);
        }
      }
    } else if (startsWith(log, "#HierarchyOfConstraint#END")) {
      expValid = false;
    }
  }
  if (startsWith(log, "#Constraint#START")) {
    std::list<std::string> strName = split(log, SEPARATOR); // "#Constraint#START", "<name>", "<runtime>"
    std::list<std::string>::iterator itr = strName.begin();
    std::string garbage(*(itr++));
    strHeadString = *(itr++);
    strRuntime = *(itr++);
    valid = strRuntime.compare("t") == 0 ? true : false;
  } else if (startsWith(log, "#Constraint#EXPRESSION")) {
    if (valid) {
      std::list<std::string> strContents = split(log, EXP_SEP); // "#Constraint#EXPRESSION", "<hierarchy>", "<expressionText>", "<result>"
      std::list<std::string>::iterator itr = strContents.begin();
      std::string garbage(*(itr++));
      std::string hierarchy(*(itr++));
      std::string expressionText(*(itr++));
      std::string strInput;
      if (strContents.size() == 3) {
        strInput = strHeadString + EXP_SEP + hierarchy + EXP_SEP + expressionText;
      } else if (strContents.size() == 4) {
        std::string result(*(itr++));
        strInput = strHeadString + EXP_SEP + hierarchy + EXP_SEP + expressionText + EXP_SEP + result;
      } else if (strContents.size() > 4) {
        int index = log.find(hierarchy) + hierarchy.length() + 1;
        strInput = strHeadString + EXP_SEP + hierarchy + EXP_SEP + log.substr(index) + EXP_SEP + strType;
      }
      if (std::find(outputtedLogs.begin(), outputtedLogs.end(), strInput) == outputtedLogs.end()) {
        outputtedLogs.push_back(strInput);
        write(strInput);
      }
    }
  } else if (startsWith(log, "#Constraint#END")) {
    valid = false;
  }
}
#endif

HA729_hierarchy::HA729_hierarchy()
{
}

HA729_hierarchy::~HA729_hierarchy()
{
}

void HA729_hierarchy::SetUp()
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new rba::RBAArbitrator(model_);
}

void HA729_hierarchy::TearDown()
{
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
#ifdef RBA_USE_LOG
  rba::RBALogManager::setLogManager(nullptr);
#endif
}

#ifdef RBA_USE_LOG
TEST_F(HA729_hierarchy, exec)
{
  collector_ = new ConstraintLogCollector();
  ASSERT_TRUE(collector_->open(LOGFILE));
  logm_ = new rba::RBALogManager();
  logm_->addCoverageLogCollector(collector_);
  rba::RBALogManager::setLogManager(logm_);

  std::unique_ptr<rba::RBAResult> result;

  result = arb_->execute(u8"C1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  result = arb_->execute(u8"C2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  result = arb_->execute(u8"C3/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  result = arb_->execute(u8"C4/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  result = arb_->execute(u8"C5/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  delete collector_;
  delete logm_;
}
#endif

}
