/// 制約式情報クラスヘッダファイル

#ifndef RBACONSTRAINTINFO_HPP
#define RBACONSTRAINTINFO_HPP

#include <cstdint>
#include <memory>
#include <set>
#include <vector>
#include "RBAExecuteResult.hpp"
#include "RBADllExport.hpp"

namespace rba {

class RBAAllocatable;
class RBAExpression;

class DLL_EXPORT RBAConstraintInfo
{
public:
  RBAConstraintInfo()=default;
  RBAConstraintInfo(const RBAConstraintInfo&)=delete;
  RBAConstraintInfo(const RBAConstraintInfo&&)=delete;
  RBAConstraintInfo& operator=(const RBAConstraintInfo&)=delete;
  RBAConstraintInfo& operator=(const RBAConstraintInfo&&)=delete;
  virtual ~RBAConstraintInfo()=default;

public:
  void setExpression(const RBAExpression* const expression);
  const RBAExpression* getExpression() const;
  void addOperandAllocatable(const RBAAllocatable* const operandAllocatable);
  void setResult(const RBAExecuteResult result);
  RBAConstraintInfo* getChild(const std::uint32_t index) const;
  void setChild(const std::shared_ptr<RBAConstraintInfo> info);
  void addTrueAllocatable(const RBAAllocatable* const allocatable);
  void addFalseAllocatable(const RBAAllocatable* const allocatable);
  void addTrueAllocatableFromOperand();
  void addFalseAllocatableFromOperand();
  void clearFalseAllocatable();
  const bool isImplies() const;
  void clear();

  bool isExceptionBeforeArbitrate() const;
  void setExceptionBeforeArbitrate(const bool exceptionBeforeArbitrate);

  /// @brief 再調停要否を判断する
  /// @param [in] allocatable 調停中のアロケータブル
  /// @param [in] isImplies 制約式は含意構文を含んでいるか
  /// @return 再調停要否( true 要 / false 否 )
  bool needsRearbitrationFor(const RBAAllocatable* const allocatable,
                             bool isImplies = false) const;

  bool needsReRearbitrationFor(const RBAAllocatable* const allocatable) const;
  void collectRearbitrationTargetFor(const RBAAllocatable* const allocatable,
				     std::set<const RBAAllocatable*>& targets,
				     const bool isNot) const;
  void collectTrueAllocatables(std::set<const RBAAllocatable*>& allocatables) const;
  void collectFalseAllocatables(std::set<const RBAAllocatable*>& allocatables) const;
  bool contains(const RBAAllocatable* const allocatable) const;
  bool isTrue() const;
  bool isFalse() const;

  /// @brief 影響を与えたエリア/ゾーンの抽出
  /// @param [in] isRevert 否定文脈( true 中 / false 外 )
  /// @param [out] affectAllocatables 影響アロケータブルリスト
  /// @param [out] collecting 収集対象文脈( true 中 / false 外 )
  /// @param [out] forObject ReferenceObject文脈( true 中 / false 外 )
  /// @return 再調停要否( true 要 / false 否 )
  void collectAffectedAllocatables(
      const bool isRevert, std::set<const RBAAllocatable*>& affectAllocatables,
      const bool collecting,
      const bool forObject);

private:
  bool isRevert() const;
  bool isSizeOperator() const;

private:
  bool exceptionBeforeArbitrate_ {false};
  const RBAExpression* expression_ {nullptr};
  RBAExecuteResult result_ {RBAExecuteResult::SKIP};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::set<const RBAAllocatable*> trueAllocatables_;
  std::set<const RBAAllocatable*> falseAllocatables_;
  std::set<const RBAAllocatable*> operandAllocatable_;
  const std::set<const RBAAllocatable*> emptyAllocatables_; // 空のsetを応答するために使用する
  mutable std::vector<std::shared_ptr<RBAConstraintInfo>> children_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

}

#endif
