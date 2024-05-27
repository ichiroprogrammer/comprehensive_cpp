#include "gtest_wrapper.h"

#include "arch_pkg.h"

namespace Dependency {
namespace {

using FileUtils::Paths_t;

DepRels_t const dep_rels_simple{
    {DepRelation{"A", 1, Paths_t{"b.h"}, "B", 0, Paths_t{}}},
};

DepRels_t const dep_rels_simple2{
    {DepRelation{"X", 1, Paths_t{"b"}, "X/A", 0, Paths_t{}}},
    {DepRelation{"X", 1, Paths_t{"c"}, "X/B", 0, Paths_t{}}},
    {DepRelation{"X", 1, Paths_t{"d"}, "X/C", 0, Paths_t{}}},
    {DepRelation{"X", 0, Paths_t{}, "X/D", 0, Paths_t{}}},
    {DepRelation{"X", 0, Paths_t{}, "X/E", 0, Paths_t{}}},

    {DepRelation{"X/A", 1, Paths_t{"b"}, "X/B", 0, Paths_t{}}},
    {DepRelation{"X/B", 1, Paths_t{"c"}, "X/C", 0, Paths_t{}}},
    {DepRelation{"X/C", 1, Paths_t{"d"}, "X/D", 0, Paths_t{}}},
    {DepRelation{"X/A", 0, Paths_t{"a"}, "X/D", 1, Paths_t{}}},
    {DepRelation{"X/A", 1, Paths_t{"a"}, "X/E", 1, Paths_t{"d"}}},
};

DepRels_t const dep_rels_simple3{
    // A -> B
    // A -> C -> D -> A
    //      C -> B
    {DepRelation{"A", 1, Paths_t{}, "B", 0, Paths_t{}}},
    {DepRelation{"A", 1, Paths_t{}, "C", 0, Paths_t{"a"}}},
    {DepRelation{"A", 0, Paths_t{}, "D", 1, Paths_t{"a"}}},

    {DepRelation{"B", 0, Paths_t{}, "C", 1, Paths_t{"b"}}},
    {DepRelation{"B", 0, Paths_t{}, "D", 0, Paths_t{}}},
    {DepRelation{"C", 1, Paths_t{"d"}, "D", 0, Paths_t{}}},
};

DepRels_t const dep_rels_middle{
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app1/mod2/mod2_2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2/mod2_1", 1, Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
                 "ut_data/app1/mod2/mod2_2", 2, Paths_t{"ut_data/app1/mod2/mod2_1/mod2_1_1.h"}}},
};

DepRels_t const dep_rels_complex{
    {DepRelation{"ut_data/app1", 2,
                 Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"},
                 "ut_data/app1/mod1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app1/mod2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app1/mod2/mod2_2", 1,
                 Paths_t{"ut_data/app1/a_1_cpp.h"}}},
    {DepRelation{"ut_data/app1", 0, Paths_t{}, "ut_data/app2", 1,
                 Paths_t{"ut_data/app1/a_2_cpp.hpp"}}},
    {DepRelation{"ut_data/app1/mod1", 1, Paths_t{"ut_data/app1/mod2/mod2_1.hpp"},
                 "ut_data/app1/mod2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod1", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod1", 1, Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
                 "ut_data/app1/mod2/mod2_2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod1", 0, Paths_t{}, "ut_data/app2", 2,
                 Paths_t{"ut_data/app1/mod1/mod1_1.hpp", "ut_data/app1/mod1/mod1_2.hpp"}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app1/mod2/mod2_1", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app1/mod2/mod2_2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2", 0, Paths_t{}, "ut_data/app2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2/mod2_1", 1, Paths_t{"ut_data/app1/mod2/mod2_2/mod2_2_1.h"},
                 "ut_data/app1/mod2/mod2_2", 2, Paths_t{"ut_data/app1/mod2/mod2_1/mod2_1_1.h"}}},
    {DepRelation{"ut_data/app1/mod2/mod2_1", 0, Paths_t{}, "ut_data/app2", 0, Paths_t{}}},
    {DepRelation{"ut_data/app1/mod2/mod2_2", 0, Paths_t{}, "ut_data/app2", 0, Paths_t{}}},
};

TEST(arch_pkg, ArchPkgSimple)
{
    auto const arch = ArchPkg::GenArch(dep_rels_simple);

    ASSERT_EQ(2, arch.size());

    auto const& a = *arch.cbegin();
    ASSERT_EQ("A", a->Name());
    ASSERT_EQ(nullptr, a->Parent());
    ASSERT_EQ("B", a->DependOn().front()->Name());
    ASSERT_FALSE(a->IsCyclic());
    ASSERT_FALSE(a->IsCyclic(*a->DependOn().front()));

    auto const& children = a->Children();
    ASSERT_EQ(0, children.size());

    auto const& b = *std::next(arch.cbegin());
    ASSERT_EQ("B", b->Name());
    ASSERT_EQ(nullptr, b->Parent());

    ASSERT_EQ(0, b->DependOn().size());
    ASSERT_FALSE(b->IsCyclic());
}

TEST(arch_pkg, ArchPkgSimple2)
{
    auto const arch = ArchPkg::GenArch(dep_rels_simple2);

    auto exp = std::string{
        "package  :X\n"
        "fullname :X\n"
        "parent   :TOP\n"
        "depend_on: {\n"
        "    A : STRAIGHT\n"
        "    B : STRAIGHT\n"
        "    C : STRAIGHT\n"
        "}\n"
        "children : {\n"
        "    package  :A:CYCLIC\n"
        "    fullname :X/A\n"
        "    parent   :X\n"
        "    depend_on: {\n"
        "        B : CYCLIC\n"
        "        E : CYCLIC\n"
        "    }\n"
        "    children : { }\n"
        "\n"
        "    package  :B:CYCLIC\n"
        "    fullname :X/B\n"
        "    parent   :X\n"
        "    depend_on: {\n"
        "        C : CYCLIC\n"
        "    }\n"
        "    children : { }\n"
        "\n"
        "    package  :C:CYCLIC\n"
        "    fullname :X/C\n"
        "    parent   :X\n"
        "    depend_on: {\n"
        "        D : CYCLIC\n"
        "    }\n"
        "    children : { }\n"
        "\n"
        "    package  :D:CYCLIC\n"
        "    fullname :X/D\n"
        "    parent   :X\n"
        "    depend_on: {\n"
        "        A : CYCLIC\n"
        "    }\n"
        "    children : { }\n"
        "\n"
        "    package  :E:CYCLIC\n"
        "    fullname :X/E\n"
        "    parent   :X\n"
        "    depend_on: {\n"
        "        A : CYCLIC\n"
        "    }\n"
        "    children : { }\n"
        "}"};

    ASSERT_EQ(exp, ToStringArch(arch));
}

TEST(arch_pkg, ArchPkgSimple3)
{
    auto const arch = ArchPkg::GenArch(dep_rels_simple3);

    auto exp = std::string{
        "package  :A:CYCLIC\n"
        "fullname :A\n"
        "parent   :TOP\n"
        "depend_on: {\n"
        "    B : STRAIGHT\n"
        "    C : CYCLIC\n"
        "}\n"
        "children : { }\n"
        "\n"
        "package  :B\n"
        "fullname :B\n"
        "parent   :TOP\n"
        "depend_on: { }\n"
        "children : { }\n"
        "\n"
        "package  :C:CYCLIC\n"
        "fullname :C\n"
        "parent   :TOP\n"
        "depend_on: {\n"
        "    B : STRAIGHT\n"
        "    D : CYCLIC\n"
        "}\n"
        "children : { }\n"
        "\n"
        "package  :D:CYCLIC\n"
        "fullname :D\n"
        "parent   :TOP\n"
        "depend_on: {\n"
        "    A : CYCLIC\n"
        "}\n"
        "children : { }"};

    ASSERT_EQ(exp, ToStringArch(arch));
}

TEST(arch_pkg, ArchPkg2)
{
    auto const arch = ArchPkg::GenArch(dep_rels_middle);

    ASSERT_EQ(1, arch.size());

    Arch_t const* mod2_children(nullptr);
    {
        auto const& mod2 = *arch.cbegin();

        ASSERT_EQ("mod2", mod2->Name());
        ASSERT_EQ(nullptr, mod2->Parent());
        ASSERT_EQ(0, mod2->DependOn().size());
        ASSERT_FALSE(mod2->IsCyclic());

        mod2_children = &mod2->Children();
        ASSERT_EQ(2, mod2_children->size());
    }
    {
        auto const& mod2_1 = *mod2_children->cbegin();
        ASSERT_EQ("mod2_1", mod2_1->Name());
        ASSERT_EQ("mod2", mod2_1->Parent()->Name());
        ASSERT_EQ("mod2_2", mod2_1->DependOn().front()->Name());
        ASSERT_TRUE(mod2_1->IsCyclic());
        ASSERT_TRUE(mod2_1->IsCyclic(*mod2_1->DependOn().front()));

        auto const& children = mod2_1->Children();
        ASSERT_EQ(0, children.size());
    }
    {
        auto const& mod2_2 = *std::next(mod2_children->cbegin());
        ASSERT_EQ("mod2_2", mod2_2->Name());
        ASSERT_EQ("mod2", mod2_2->Parent()->Name());
        ASSERT_EQ("mod2_1", mod2_2->DependOn().front()->Name());
        ASSERT_TRUE(mod2_2->IsCyclic());
        ASSERT_TRUE(mod2_2->IsCyclic(*mod2_2->DependOn().front()));

        auto const& children = mod2_2->Children();
        ASSERT_EQ(0, children.size());
    }
}

TEST(arch_pkg, ArchPkg3)
{
    auto const arch = ArchPkg::GenArch(dep_rels_complex);

    /* std::cout << ToStringArch(arch) << std::endl;

        package  :app1:CYCLIC
        parent   :TOP
        depend_on: {
            mod1
        }
        children : {
            package  :mod1:CYCLIC
            parent   :app1
            depend_on: {
                mod2
                mod2_2
            }

            package  :mod2
            parent   :app1
            children : {
                package  :mod2_1:CYCLIC
                parent   :mod2
                depend_on: {
                    mod2_2
                }

                package  :mod2_2:CYCLIC
                parent   :mod2
                depend_on: {
                    app1
                    mod2_1
                }
            }
        }
        package  :app2
        parent   :TOP
        depend_on: {
            app1
            mod1
        }
    */

    {
        Arch_t const* app1_children(nullptr);
        {
            auto const& app1 = *arch.cbegin();

            ASSERT_EQ("app1", app1->Name());
            ASSERT_EQ(nullptr, app1->Parent());
            ASSERT_EQ(1, app1->DependOn().size());
            {
                auto const& depend = app1->DependOn();

                ASSERT_EQ("mod1", (*depend.cbegin())->Name());
                ASSERT_TRUE(app1->IsCyclic(*(*depend.cbegin())));
            }

            ASSERT_TRUE(app1->IsCyclic());

            app1_children = &app1->Children();
            ASSERT_EQ(2, app1_children->size());
        }
        {
            {
                auto const& mod1 = *app1_children->cbegin();
                ASSERT_EQ("mod1", mod1->Name());
                ASSERT_EQ("app1", mod1->Parent()->Name());
                ASSERT_EQ(2, mod1->DependOn().size());
                {
                    auto const& depend = mod1->DependOn();

                    ASSERT_EQ("mod2", (*depend.cbegin())->Name());
                    ASSERT_FALSE(mod1->IsCyclic(*(*depend.cbegin())));

                    auto const next = *std::next(depend.cbegin());
                    ASSERT_EQ("mod2_2", next->Name());
                    ASSERT_TRUE(mod1->IsCyclic(*next));
                }
                ASSERT_TRUE(mod1->IsCyclic());
            }
            Arch_t const* mod2_children(nullptr);
            {
                auto const& mod2 = *std::next(app1_children->cbegin());
                ASSERT_EQ("mod2", mod2->Name());
                ASSERT_EQ("app1", mod2->Parent()->Name());
                ASSERT_EQ(0, mod2->DependOn().size());

                mod2_children = &mod2->Children();
                ASSERT_EQ(2, mod2_children->size());

                ASSERT_FALSE(mod2->IsCyclic());
            }
            {
                {
                    auto const& mod2_1 = *mod2_children->cbegin();
                    ASSERT_EQ("mod2_1", mod2_1->Name());

                    ASSERT_EQ("mod2", mod2_1->Parent()->Name());
                    ASSERT_EQ(1, mod2_1->DependOn().size());
                    {
                        auto const& depend = mod2_1->DependOn();
                        ASSERT_EQ("mod2_2", (*depend.cbegin())->Name());
                        ASSERT_TRUE(mod2_1->IsCyclic(*(*depend.cbegin())));
                    }

                    ASSERT_TRUE(mod2_1->IsCyclic());
                    ASSERT_EQ(0, mod2_1->Children().size());
                }
                {
                    auto const& mod2_2 = *std::next(mod2_children->cbegin());
                    ASSERT_EQ("mod2_2", mod2_2->Name());

                    ASSERT_EQ("mod2", mod2_2->Parent()->Name());
                    ASSERT_EQ(2, mod2_2->DependOn().size());
                    {
                        auto const& depend = mod2_2->DependOn();
                        ASSERT_EQ("app1", (*depend.cbegin())->Name());
                        ASSERT_TRUE(mod2_2->IsCyclic(*(*depend.cbegin())));

                        auto const next = *std::next(depend.cbegin());
                        ASSERT_EQ("mod2_1", (*std::next(depend.cbegin()))->Name());
                        ASSERT_TRUE(mod2_2->IsCyclic(*next));
                    }

                    ASSERT_TRUE(mod2_2->IsCyclic());
                    ASSERT_EQ(0, mod2_2->Children().size());
                }
            }
        }
    }
    {
        auto const& app2 = *std::next(arch.cbegin());

        ASSERT_EQ("app2", app2->Name());
        ASSERT_EQ(nullptr, app2->Parent());
        ASSERT_EQ(2, app2->DependOn().size());
        {
            auto const& depend = app2->DependOn();

            ASSERT_EQ("app1", (*depend.cbegin())->Name());
            ASSERT_EQ("mod1", (*std::next(depend.cbegin()))->Name());
        }

        ASSERT_FALSE(app2->IsCyclic());
        ASSERT_EQ(0, app2->Children().size());
    }
}

TEST(arch_pkg, ToPlantUML_Rectangle)
{
    {
        auto const arch = ArchPkg::GenArch(dep_rels_simple);
        auto const exp  = std::string{
            "rectangle \"A\" as A\n"
             "rectangle \"B\" as B"};
        ASSERT_EQ(exp, ToPlantUML_Rectangle(arch));
    }
    {
        auto const arch = ArchPkg::GenArch(dep_rels_middle);
        auto const exp  = std::string{
            "rectangle \"mod2\" as ut_data___app1___mod2 {\n"
             "    rectangle \"mod2_1\" as ut_data___app1___mod2___mod2_1\n"
             "    rectangle \"mod2_2\" as ut_data___app1___mod2___mod2_2\n"
             "}"};
        ASSERT_EQ(exp, ToPlantUML_Rectangle(arch));
    }
    {
        auto const arch = ArchPkg::GenArch(dep_rels_complex);
        auto const exp  = std::string{
            "rectangle \"app1\" as ut_data___app1 {\n"
             "    rectangle \"mod1\" as ut_data___app1___mod1\n"
             "    rectangle \"mod2\" as ut_data___app1___mod2 {\n"
             "        rectangle \"mod2_1\" as ut_data___app1___mod2___mod2_1\n"
             "        rectangle \"mod2_2\" as ut_data___app1___mod2___mod2_2\n"
             "    }\n"
             "}\n"
             "rectangle \"app2\" as ut_data___app2"};
        ASSERT_EQ(exp, ToPlantUML_Rectangle(arch));
    }
}

TEST(arch_pkg, ToPlantUML_Rectangle2)
{
    auto const arch = ArchPkg::GenArch(dep_rels_complex);
    auto const exp  = std::string{
        "ut_data___app1 \"2\" -[#orange]-> ut_data___app1___mod1\n"
         "ut_data___app1___mod2___mod2_2 \"1\" -[#orange]-> ut_data___app1\n"
         "ut_data___app2 \"1\" -[#green]-> ut_data___app1\n"
         "ut_data___app1___mod1 \"1\" -[#green]-> ut_data___app1___mod2\n"
         "ut_data___app1___mod1 \"1\" -[#orange]-> ut_data___app1___mod2___mod2_2\n"
         "ut_data___app2 \"2\" -[#green]-> ut_data___app1___mod1\n"
         "ut_data___app1___mod2___mod2_1 \"1\" <-[#red]-> \"2\" ut_data___app1___mod2___mod2_2"};

    ASSERT_EQ(exp, ToPlantUML_Rectangle(arch, dep_rels_complex));
}

TEST(arch_pkg, HasCyclicDeps)
{
    {
        auto const arch = ArchPkg::GenArch(dep_rels_simple);
        ASSERT_FALSE(HasCyclicDeps(arch, dep_rels_simple));
    }
    {
        auto const arch = ArchPkg::GenArch(dep_rels_middle);
        ASSERT_TRUE(HasCyclicDeps(arch, dep_rels_middle));
    }
    {
        auto const arch = ArchPkg::GenArch(dep_rels_complex);
        ASSERT_TRUE(HasCyclicDeps(arch, dep_rels_complex));
    }
}

TEST(arch_pkg, FindArchPkg)
{
    auto const arch = ArchPkg::GenArch(dep_rels_simple);

    {
        ArchPkg const* pkg_a = FindArchPkgByName(arch, "A");
        ASSERT_NE(nullptr, pkg_a);
        ASSERT_EQ("A", pkg_a->Name());
    }
    {
        ArchPkg const* pkg_a_f = FindArchPkgByFullName(arch, "A");
        ASSERT_NE(nullptr, pkg_a_f);
        ASSERT_EQ("A", pkg_a_f->FullName());
    }
    {
        ArchPkg const* pkg_b = FindArchPkgByName(arch, "B");
        ASSERT_NE(nullptr, pkg_b);
        ASSERT_EQ("B", pkg_b->Name());
    }
    {
        ArchPkg const* pkg_b_f = FindArchPkgByName(arch, "B");

        ASSERT_NE(nullptr, pkg_b_f);
        ASSERT_EQ("B", pkg_b_f->FullName());
    }
}

TEST(arch_pkg, FindArchPkg2)
{
    auto const arch = ArchPkg::GenArch(dep_rels_simple2);

    {
        ArchPkg const* pkg_x = FindArchPkgByName(arch, "X");
        ASSERT_NE(nullptr, pkg_x);
        ASSERT_EQ("X", pkg_x->Name());
    }
    {
        ArchPkg const* pkg_x_f = FindArchPkgByFullName(arch, "X");
        ASSERT_NE(nullptr, pkg_x_f);
        ASSERT_EQ("X", pkg_x_f->FullName());
    }
    {
        ArchPkg const* pkg_a = FindArchPkgByName(arch, "A");
        ASSERT_NE(nullptr, pkg_a);
        ASSERT_EQ("A", pkg_a->Name());
    }
    {
        ArchPkg const* pkg_a_f = FindArchPkgByFullName(arch, "X/A");
        ASSERT_NE(nullptr, pkg_a_f);
        ASSERT_EQ("X/A", pkg_a_f->FullName());
    }
    {
        ArchPkg const* pkg_y = FindArchPkgByName(arch, "Y");
        ASSERT_EQ(nullptr, pkg_y);
    }
    {
        ArchPkg const* pkg_y_f = FindArchPkgByFullName(arch, "Y");
        ASSERT_EQ(nullptr, pkg_y_f);
    }
}

TEST(arch_pkg, FindArchPkg3)
{
    auto const arch = ArchPkg::GenArch(dep_rels_complex);

    {
        ArchPkg const* pkg_app1 = FindArchPkgByName(arch, "app1");
        ASSERT_NE(nullptr, pkg_app1);
        ASSERT_EQ("app1", pkg_app1->Name());
        ASSERT_EQ("ut_data/app1", pkg_app1->FullName());
    }
    {
        ArchPkg const* pkg_app1_f = FindArchPkgByFullName(arch, "ut_data/app1");
        ASSERT_NE(nullptr, pkg_app1_f);
        ASSERT_EQ("app1", pkg_app1_f->Name());
        ASSERT_EQ("ut_data/app1", pkg_app1_f->FullName());
    }
    {
        ArchPkg const* pkg_mod2_1 = FindArchPkgByName(arch, "mod2_1");
        ASSERT_NE(nullptr, pkg_mod2_1);
        ASSERT_EQ("mod2_1", pkg_mod2_1->Name());
        ASSERT_EQ("ut_data/app1/mod2/mod2_1", pkg_mod2_1->FullName());
    }
    {
        ArchPkg const* pkg_mod2_1_f = FindArchPkgByFullName(arch, "ut_data/app1/mod2/mod2_1");
        ASSERT_NE(nullptr, pkg_mod2_1_f);
        ASSERT_EQ("mod2_1", pkg_mod2_1_f->Name());
        ASSERT_EQ("ut_data/app1/mod2/mod2_1", pkg_mod2_1_f->FullName());
    }
}
}  // namespace
}  // namespace Dependency
