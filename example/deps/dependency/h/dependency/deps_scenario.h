#pragma once
#include <memory>
#include <string>
#include <vector>

#include "file_utils/path_utils.h"

namespace Dependency {

class ScenarioGenerator {
public:
    virtual bool Output(std::ostream& os) const = 0;
    virtual ~ScenarioGenerator() {}
};

class PkgGenerator : public ScenarioGenerator {
public:
    explicit PkgGenerator(std::string const& in, bool recursive, FileUtils::Paths_t const& dirs_opt,
                          std::string const& pattern);
    virtual bool Output(std::ostream& os) const override;

private:
    FileUtils::Paths_t const dirs_;
};

class SrcsGenerator : public ScenarioGenerator {
public:
    explicit SrcsGenerator(std::string const& in, bool recursive,
                           FileUtils::Paths_t const& dirs_opt, std::string const& pattern);
    virtual bool Output(std::ostream& os) const override;

private:
    FileUtils::Paths_t const dirs_;
};

class Pkg2SrcsGenerator : public ScenarioGenerator {
public:
    explicit Pkg2SrcsGenerator(std::string const& in, bool recursive, bool src_as_pkg,
                               FileUtils::Paths_t const& dirs_opt, std::string const& pattern);
    virtual bool Output(std::ostream& os) const override;

private:
    FileUtils::Dirs2Srcs_t const dirs2srcs_;
};

class Pkg2PkgGenerator : public ScenarioGenerator {
public:
    explicit Pkg2PkgGenerator(std::string const& in, bool recursive, bool src_as_pkg,
                              FileUtils::Paths_t const& dirs_opt, std::string const& pattern);
    virtual bool Output(std::ostream& os) const override;

private:
    FileUtils::Dirs2Srcs_t const dirs2srcs_;
};

class ArchGenerator : public ScenarioGenerator {
public:
    explicit ArchGenerator(std::string const& in);
    virtual bool Output(std::ostream& os) const override;
    ~ArchGenerator();

protected:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

class Arch2PUmlGenerator : public ArchGenerator {
public:
    explicit Arch2PUmlGenerator(std::string const& in);
    virtual bool Output(std::ostream& os) const override;
};

class CyclicGenerator : public ArchGenerator {
public:
    explicit CyclicGenerator(std::string const& in);
    virtual bool Output(std::ostream& os) const override;

private:
    bool has_cyclic_dep_;
};
}  // namespace Dependency
