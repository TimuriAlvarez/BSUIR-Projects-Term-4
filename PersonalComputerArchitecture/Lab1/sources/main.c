#include "tlib.h"

int main(void)
{
	T_CLASS(TConsole, default_constructor)();

	TMessage options[] = { "Writing mode", "Reading mode", nullptr };
	const T_CONTAINER(TMenu, void, Action) actions[] = { &writing_mode, &reading_mode };
	T_CONTAINER(TMenu, void, menu)(options, actions, nullptr);

	return 0;
}
