// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA864_covlog.cpp
 */

#ifdef RBA_USE_LOG
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include "RBAJsonParser.hpp"
#include "RBAModelImpl.hpp"
#include "HA864_covlog.hpp"
#include "TestCommon.hpp"
#include "RBAModelImpl.hpp"

namespace {

std::string ExpectLog = u8R"()";

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
 * MatrixLogCollector
 */
MatrixLogCollector::MatrixLogCollector() {}
MatrixLogCollector::~MatrixLogCollector() {}

void MatrixLogCollector::log(const std::string& log)
{
  if (startsWith(log, "#TCSTART")) {
    // テストケース開始のため前回Requestをクリア
    previousRequestList.clear();
  } else if (startsWith(log, "#START")) {
    testCaseList.push_back(log);
  } else if (startsWith(log, "#PrevResult")) {
    testCaseList.push_back(log);
  } else if (startsWith(log, "#Request#C")) {
    presentRequestList.push_back(log);
  } else if (startsWith(log, "#Result")) {
    resultList.push_back(log);
  } else if (startsWith(log, "#CanceledRequest")) {
    cancelRequestList.push_back(log);
  } else if (startsWith(log, "#END")) {
    if (previousRequestList.size() == 0) {
      // 初回
      // orderが一番大きいRequestを取得
      presentRequestList.sort([](const std::string x, const std::string y) {
				return std::stoi(x.substr(x.find_last_of(",") + 1)) > std::stoi(y.substr(y.find_last_of(",") + 1));
			      });
      testCaseList.push_back(*presentRequestList.begin());
    }
    else {
      // 前回Requestあり
      auto prevItr = previousRequestList.begin();
      auto prevEnd = previousRequestList.end();
      auto presItr = presentRequestList.begin();
      auto presEnd = presentRequestList.end();

      while (prevItr != prevEnd && presItr != presEnd) {
	if (hasDiffRequest(*prevItr, *presItr)) {
	  // 差分のあるRequestがあれば取得
	  testCaseList.push_back(*presItr);
	  break;
	}
	prevItr++;
	presItr++;
      }
    }
    testCaseList.insert(testCaseList.end(), resultList.begin(), resultList.end());
    testCaseList.insert(testCaseList.end(), cancelRequestList.begin(), cancelRequestList.end());
    testCaseList.push_back(log);
    for (std::string l : testCaseList) {
      write(l);
    }
    testCaseList.clear();
    previousRequestList.clear();
    previousRequestList.insert(previousRequestList.end(), presentRequestList.begin(), presentRequestList.end());
    presentRequestList.clear();
    resultList.clear();
    cancelRequestList.clear();
  }
}

bool MatrixLogCollector::hasDiffRequest(const std::string& prevLogLine,
					const std::string& presLogLine)
{
  // orderは更新されることがあるため、比較から除外する
  return prevLogLine.substr(0, prevLogLine.find_last_of(",")).compare(presLogLine.substr(0, presLogLine.find_last_of(",")));
}

/*
 * HA864_covlog
 */
HA864_covlog::HA864_covlog() {}
HA864_covlog::~HA864_covlog() {}

void HA864_covlog::SetUp()
{
  rba::RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  collector_ = new MatrixLogCollector();
  ASSERT_TRUE(collector_->open(LOGFILE));
  logm_ = new rba::RBALogManager();
  logm_->addCoverageLogCollector(collector_);
  rba::RBALogManager::setLogManager(logm_);
  arb_ = new rba::RBAArbitrator(model_, logm_);
}

void HA864_covlog::TearDown()
{
  if(arb_) {
    delete arb_;
    arb_ = nullptr;
  }
  if(model_) {
    delete model_;
    model_ = nullptr;
  }
  if(logm_) {
    rba::RBALogManager::setLogManager(nullptr);
    delete logm_;
    logm_ = nullptr;
  }
  if(collector_) {
    delete collector_;
    collector_ = nullptr;
  }
}

bool HA864_covlog::checklog(const std::string& msg,
			    const std::string& expect_str)
{
  std::list<std::string> expLines;
  std::stringstream ss(expect_str);
  std::string buf;
  while( std::getline(ss, buf, '\n')) {
    if(buf.length() > 0) {
      expLines.push_back(buf);
    }
  }

  // ログの比較
  std::ifstream ifs(LOGFILE);
  std::string expLine;
  if(ifs.fail()) {
    std::cerr << "[ERROR] " << LOGFILE << ": No such file or directory"
	      << std::endl;
    //return false;
  }
  std::string line;
  int lineNum = 0;
  while(getline(ifs, line)) {
    // ログ一行取り出し
    lineNum += 1;
    if(line.length() == 0) {
      continue;
    }
    if(expLines.size() == 0) {
      std::cerr << "[ERROR] No expect string, " << line << std::endl;
      return false;
    }
    // 期待値一行取り出し
    expLine = expLines.front();
    expLines.pop_front();
    // 比較
    if(line != expLine) {
      std::cerr << "[ERROR] " << lineNum << ": \""
		<< expLine << "\", \"" << line << "\""
		<< std::endl;
      return false;
    }
  }
  if(expLines.size() > 0) {
    expLine = expLines.front();
    std::cerr << "[ERROR] \"" << expLine << "\"" << std::endl;
    return false;
  }

  return true;
}

const std::string CASE1_EXPECT = R"(
#START
#Request#C,on,Content1,State1,1
#Result#A,Area1,Content1
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
#START
#PrevResult#A,Area1,Content1,State1
#Request#C,on,Content2,State2,2
#Result#A,Area1,Content2
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
)";

TEST_F(HA864_covlog, case1)
{
  std::unique_ptr<rba::RBAResult> result;

  arb_->clearArbitration();
  collector_->log("#START");
  result = arb_->execute(u8"Content1/State1", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  collector_->log("#START");
  result = arb_->execute(u8"Content2/State2", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  EXPECT_TRUE(checklog("case1", CASE1_EXPECT));
}

const std::string CASE2_EXPECT = R"(
#START
#PrevResult#A,Area1,Content3,State3
#Request#C,on,Content1,State1,2
#Result#A,Area1,Content1
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
#START
#PrevResult#A,Area1,Content1,State1
#Request#C,on,Content2,State2,3
#Result#A,Area1,Content2
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
)";

TEST_F(HA864_covlog, case2)
{
  std::unique_ptr<rba::RBAResult> result;

  arb_->clearArbitration();
  collector_->log("#START");
  EXPECT_TRUE(arb_->setAllocatableResult(u8"Area1", u8"Content3"));
  result = arb_->execute(u8"Content1/State1", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  collector_->log("#START");
  result = arb_->execute(u8"Content2/State2", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  EXPECT_TRUE(checklog("case2", CASE2_EXPECT));
}

const std::string HIDDEN_EXPECT = R"(
#START
#Request#C,on,Content1,State1,1
#Result#A,Area1,Content1
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
#START
#PrevResult#A,Area1,Content1,State1
#Request#C,on,Content4,NORMAL,2
#Result#A,Area1,
#Result#A,Area2,Content4
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
#START
#PrevResult#A,Area2,Content4,NORMAL
#Result#A,Area1,
#Result#A,Area2,Content4
#Result#A,Zone1,
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
)";

TEST_F(HA864_covlog, hidden)
{
  std::unique_ptr<rba::RBAResult> result;

  arb_->clearArbitration();
  collector_->log("#START");
  result = arb_->execute(u8"Content1/State1", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  collector_->log("#START");
  result = arb_->execute(u8"Content4/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  collector_->log("#START");
  result = arb_->execute(u8"", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  EXPECT_TRUE(checklog("hidden", HIDDEN_EXPECT));
}

const std::string MUTE_EXPECT = R"(
#START
#Request#C,on,SContent1,NORMAL,1
#Result#A,Area1,
#Result#A,Area2,
#Result#A,Zone1,SContent1
#Result#A,Zone2,
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
#START
#PrevResult#A,Zone1,SContent1,NORMAL
#Request#C,off,Content1,State1,0
#Result#A,Area1,
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,SContent2
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
#START
#PrevResult#A,Zone2,SContent2,NORMAL
#Result#A,Area1,
#Result#A,Area2,
#Result#A,Zone1,
#Result#A,Zone2,SContent2
#CanceledRequest#Content1,State1,f
#CanceledRequest#Content2,State2,f
#CanceledRequest#Content3,State3,f
#CanceledRequest#Content4,NORMAL,f
#CanceledRequest#SContent1,NORMAL,f
#CanceledRequest#SContent2,NORMAL,f
#END
)";

TEST_F(HA864_covlog, mute)
{
  std::unique_ptr<rba::RBAResult> result;

  arb_->clearArbitration();
  collector_->log("#START");
  result = arb_->execute(u8"SContent1/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  collector_->log("#START");
  result = arb_->execute(u8"SContent2/NORMAL", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  collector_->log("#START");
  result = arb_->execute(u8"", true);
  EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  collector_->log("#END");

  EXPECT_TRUE(checklog("mute", MUTE_EXPECT));
}

}
#endif
