#include "Application.h"

int main() {
	EventSystem e;
	Application app{e};
	app.Run();

    return 0;
}
