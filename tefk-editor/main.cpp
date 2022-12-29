#include "app.hpp"

int main(int argc, char** argv) {
	tefk::Application app;
	app.Init(argc, argv);
	app.Run();
}