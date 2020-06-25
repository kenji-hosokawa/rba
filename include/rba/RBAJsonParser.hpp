// Copyright (c) 2018 DENSO CORPORATION. All rights reserved.
/**
 * JSONパーサークラス
 */

#ifndef RBAJSONPARSER_HPP
#define RBAJSONPARSER_HPP

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <memory>
#include "RBAModel.hpp"

namespace rba
{

class RBAModel;
// internal {
class RBAExpression;
class RBAModelFactory;
// }

/**
 * @cond japanese
 * @class RBAJsonParser
 * JSON形式のモデル情報を読み込み、モデルオブジェクトを生成する機能を提供する。
 * @endcond
 *
 * @cond english
 * @class RBAJsonParser
 * Provides the facility that loads a model file in JSON format and generate a Model object.
 * @enum
 * @endcond
 */
class DLL_EXPORT RBAJsonParser
{
public:
  RBAJsonParser();
  RBAJsonParser(const RBAJsonParser&)=delete;
  RBAJsonParser(const RBAJsonParser&&)=delete;
  RBAJsonParser& operator=(const RBAJsonParser&)=delete;
  RBAJsonParser& operator=(const RBAJsonParser&&)=delete;
  virtual ~RBAJsonParser() noexcept;

public:
  /**
   * @cond japanese
   * @brief JSONファイルを読み込んでモデルを生成する
   * @param filename JSONファイルのファイルパス
   * @return モデル
   * ファイルが存在しない場合はnullptrを返す。
   *
   * **使用例：**
   *
   * @endcond
   *
   * @cond english
   * @brief Loads a JSON file and generates a model object.
   * @param filename Path of JSON file
   * @return Model
   * If the file is not found, returns nullptr.
   *
   * **Example**
   *
   * @endcond
   * ```
   *    rba::RBAJsonParser parser;
   *    rba::RBAModel* model = parser.parse("RBAModel.json");
   *    if(model == nullptr) {
   *        std::cout << "ERRROR: Could not read JSON file" << std::endl;
   *        return 1;
   *    }
   *    rba::RBAArbitrator* arb = new rba::RBAArbitrator(model);
   * ```
   */
  RBAModel* parse(const std::string& filename);

  // internal {
  RBAJsonParser(RBAModelFactory* factory);
  // }

private:
  class Impl;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<Impl> impl_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
