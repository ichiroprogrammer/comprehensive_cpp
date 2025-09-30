#include <future>
#include <memory>
#include <vector>

#include "gtest_wrapper.h"

namespace {

// @@@ sample begin 0:0
// [A]
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

// [解説]
// * Observerパターンの使用について
//      * ObserverIFはModelを宣言、定義しているヘッダファイルに定義する。
//      * 何らかの理由でそうしない場合は、ObserverIFはModelを含むパッケージ内に定義する。
// * Observerパターンの導入により、
//      * ModelはViewX、ViewYに依存しなくなったが、代わりにObserverIFに依存する。
//      * この依存関係はObserverIFがModelヘッダに含まれることで問題にならない。
// * その他
//      * 通常は、Attachに対してDetachも定義するが、AttachされたオブジェクトをDetachしない
//        場合は、今回の例のようにAttachされたオブジェクトの廃棄をModelにさせた方が良い。
//      * こういった動作の確認にもForTestクラスを使用した。

class ObserverIF {
public:
    void DisplaySomething(std::string const& result) { display_something(result); }
    virtual ~ObserverIF() = default;

private:
    virtual void display_something(std::string const&) = 0;
};

class Model {
public:
    Model() = default;
    ~Model() { wait_future(); }

    // Detachできない仕様にする。その代わりにobserverの廃棄もModelに任せることができる。
    void Attach(std::unique_ptr<ObserverIF> observer) { observers_.emplace_back(std::move(observer)); }

    void DoSomething()
    {
        wait_future();

        future_ = std::async(std::launch::async, [this] {
            // 本来は非同期処理が必要な重い処理
            auto result = std::string{"result of doing something"};

            notify(result);
        });
    }

private:
    std::future<void>                        future_{};
    std::vector<std::unique_ptr<ObserverIF>> observers_{};

    void notify(std::string const& result) const
    {
        for (auto& observer : observers_) {
            observer->DisplaySomething(result);
        }
    }

    void wait_future()
    {
        if (future_.valid()) {
            future_.wait();
        }
    }
};

class ViewX : public ObserverIF {
private:
    virtual void display_something(std::string const&) override {}
};

class ViewY : public ObserverIF {
private:
    virtual void display_something(std::string const&) override {}
};

class Controller {
public:
    Controller(Model& model) : model_{model} {}
    void OK_Clicked() { model_.DoSomething(); }

    Model& model_;
};

class ForTest : public ObserverIF {
public:
    explicit ForTest(std::string& result, uint32_t& called, bool& destructed)
        : result_{result}, called_{called}, destructed_{destructed}
    {
    }
    virtual ~ForTest() override { destructed_ = true; }

private:
    virtual void display_something(std::string const& result) noexcept override
    {
        result_ = result;
        ++called_;
    }

    std::string& result_;
    uint32_t&    called_;
    bool&        destructed_;
};

TEST(DesignPatternA, Observer)
{
    auto result     = std::string{};
    auto called     = 0U;
    auto destructed = false;

    {
        auto model      = Model{};
        auto controller = Controller{model};

        model.Attach(std::make_unique<ViewX>());
        model.Attach(std::make_unique<ViewY>());
        model.Attach(std::make_unique<ForTest>(result, called, destructed));

        controller.OK_Clicked();
        controller.OK_Clicked();
        controller.OK_Clicked();
    }

    ASSERT_EQ("result of doing something", result);
    ASSERT_EQ(3, called);
    ASSERT_TRUE(destructed);
}
// @@@ sample end
}  // namespace
