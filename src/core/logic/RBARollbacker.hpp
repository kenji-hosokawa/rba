/**
 * 調停結果ロールバッククラスヘッダファイル
 */

#ifndef RBARROLLBACKER_HPP
#define RBARROLLBACKER_HPP

#include <unordered_map>
#include <memory>
#include <list>

namespace rba
{
class RBAModel;
class RBAAllocatable;
class RBAArbitrator;

class RBARollbacker
{
 public:
  RBARollbacker()=default;
  RBARollbacker(const RBARollbacker&)=delete;
  RBARollbacker(const RBARollbacker&&)=delete;
  RBARollbacker& operator=(const RBARollbacker&)=delete;
  RBARollbacker& operator=(const RBARollbacker&&)=delete;
  virtual ~RBARollbacker() noexcept;

  /**
   * 再調停中に再調停する際に子再調停用のバックアップを登録する
   * ロールバックするときに子のバックアップも元に戻す
   */
  void addChild(const std::shared_ptr<RBARollbacker> child);

  void removeChild(const std::shared_ptr<RBARollbacker> child);

  /**
   * 調停状態と影響情報をバックアップする
   * バックアップするのは直接再調停するAllocatableだけ
   * 再調停中の再調停は子にバックアップさせる
   * モデル上の全Allocatableをバックアップするのは非効率なので
   * 再調停するものだけをバックアップする
   */
  void backup(std::list<const RBAAllocatable*>& backuplist);

  /**
   * インスタンス生成時の状態に調停状態と影響情報をロールバックする
   */
  void rollback();

 private:
  /**
   * アロケータブルの調停状態をコピーする
   * @param from コピー元
   * @param to コピー先
   */
  void copyAllocatable(const RBAAllocatable* const from, RBAAllocatable* const to);

  std::list<std::shared_ptr<RBARollbacker>> children_;
  std::unordered_map<const RBAAllocatable*, std::unique_ptr<RBAAllocatable>> backupMap_; // 再調停失敗時のロールバック情報
};

}

#endif
