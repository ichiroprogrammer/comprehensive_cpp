#include <future>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [Q]
// 下記クラスはそれぞれが
//      * ViewX、 ViewY : GUIへの出力(描画)
//      * Model         : 何らかのビジネスロジックの演算
//      * Controller    : OKボタンクリックイベントをModelへ通知
// を行うことを模擬している。
// 依存関係Model->ViewX、ViewYはMVCに逆行しているため下記のような問題を持つ。
//      * ViewX、ViewYの変更がModelに伝搬してしまう。
//      * この例は単純であるためViewX、ViewY->Modelへの依存関係は存在しないが、
//        実際のアプリケーションではそのような依存関係が存在するため、依存関係が循環してしまう。
//      * ModelがダイレクトにViewX、ViewYへ出力するため、単体テストの実施は困難である。
//      * この依存関係が直接の原因ではないが、このような依存関係を持つアプリケーションのクラスは
//        巨大になる。
//  アプリケーションが小規模である時には、このような問題がバグや開発効率悪化の原因となることは稀
//  であり放置されることが多いが、大規模化に伴いこのような潜在的問題が表出する。
//  ModelにObserverパターンを適用する等をしてこの問題に対処するとともに、Modelの単体テストを行え。

class ViewX {
public:
    void DisplaySomething(std::string const&) noexcept {}
};
ViewX g_ViewX;

class ViewY {
public:
    void DisplaySomething(std::string const&) noexcept {}
};
ViewY g_ViewY;

class Model {
public:
    Model() = default;
    ~Model() { wait_future(); }

    void DoSomething()
    {
        wait_future();

        future_ = std::async(std::launch::async, [] {
            // 本来は非同期処理が必要な重い処理
            auto result = std::string{"result of doing something"};

            g_ViewX.DisplaySomething(result);
            g_ViewY.DisplaySomething(result);
        });
    }

private:
    std::future<void> future_;

    void wait_future() noexcept
    {
        if (future_.valid()) {
            future_.wait();
        }
    }
};

class Controller {
public:
    Controller(Model& model) noexcept : model_{model} {}
    void OK_Clicked() { model_.DoSomething(); }

    Model& model_;
};

TEST(DesignPatternQ, Observer)
{
    auto model      = Model{};
    auto controller = Controller{model};

    controller.OK_Clicked();
    controller.OK_Clicked();
    controller.OK_Clicked();
}
// @@@ sample end
}  // namespace
