#ifdef RBA_USE_LOG
#include <string>
#include "gtest/gtest.h"
#include "TestLogCommon.hpp"
namespace stub{
StubLogCollector::StubLogCollector(const std::string& expectedLogFilePath,
                                   const std::string& outLogFilePath,
                                   bool outputs):outputs_(outputs) {
  if (outputs_ == true) { // デバッグ時のログファイル出力用処理
    writing_file_.open(outLogFilePath, std::ios::trunc);
    EXPECT_FALSE(writing_file_.fail());
  }
  reading_file_.open(expectedLogFilePath, std::ios::in);
  EXPECT_FALSE(reading_file_.fail());
}

StubLogCollector::~StubLogCollector()
{
}

void StubLogCollector::log(const std::string& logLine) {
  if (outputs_ == true) { // デバッグ時のログファイル出力用処理
    writing_file_ << logLine <<std::endl;
  }
  std::string reading_line_buffer;
  std::string logline_buffer;
  std::stringstream l{logLine};

  // writing_file_にはendlを付け加えているので、log()の区切りとなる、最初の行が空行の可能性がある
  // 行のインデックスを合わせるための処理
  std::getline(reading_file_, reading_line_buffer);
  if (reading_line_buffer != "" ) {
    std::getline(l, logline_buffer);
    EXPECT_EQ(logline_buffer, reading_line_buffer);
  }

  while (std::getline(l, logline_buffer)) {
    std::getline(reading_file_, reading_line_buffer);
    EXPECT_EQ(logline_buffer, reading_line_buffer);
  }
}
}
void logOutputForNoReturnBugInit(){
  rba::RBALogManager::init(4);  // 全ログ出力
  // ログ設定: ALL ON
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_REQUEST, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_ALL_CONSTRAINTS, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_PREVIOUS_RESULT, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_ARBITRATE, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_CANCEL_REQUEST, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_RESULT, true);
  rba::RBALogManager::setEnable(rba::RBALogManager::TYPE_SAVE_LOG, true);
}
void logOutputForNoReturnBug(){
  sleep(2);
  std::ofstream writing_file_;
  writing_file_.open("/tmp/HA1047_all_content_request.txt", std::ios::trunc);
  writing_file_ << rba::RBALogManager::getArbitrateLog();
  exit(-1);
}
#endif
