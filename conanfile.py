"""Conan package definition for Array"""

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
from conan.tools.build import check_min_cppstd

class ArrayFile(ConanFile):

    name = "Array"
    version = "0.1.0"
    label = "array"

    settings = "os", "arch", "compiler", "build_type"

    exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "test/*"

    def build_requirements(self) -> None:
        self.tool_requires("cmake/[>=3.27.0]")
        self.tool_requires("ccache/[>=4.8.3]")
        self.tool_requires("cppcheck/[>=2.12.1]")
        self.test_requires("gtest/[>=1.14.0]")

    def validate(self) -> None:
        check_min_cppstd(self, "20")

    def layout(self) -> None:
        cmake_layout(self)

    def generate(self) -> None:
        CMakeToolchain(self).generate()
        CMakeDeps(self).generate()

    def build(self) -> None:
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self) -> None:
        cmake = CMake(self)
        cmake.install()
