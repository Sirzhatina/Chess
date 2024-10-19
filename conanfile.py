from conan import ConanFile
from conan.tools.cmake import cmake_layout

class ChessDeps(ConanFile):
	settings = "os", "arch", "compiler", "build_type"

	requires = "asio/1.31.0"
	generators = "CMakeDeps", "CMakeToolchain"

	def layout(self):
		cmake_layout(self)