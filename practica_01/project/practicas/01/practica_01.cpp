#include "practica_01.h"

#include "../../figures/fig_factory.h"
#include "../../figures/rect.h"

void practica_01::run()
{
    auto *new_rect1 = figure::fig_factory::make_rect(100.f, 100.f, 100.f, 100.f, color(1.f, 0.f, 0.f, 1.f));
    auto *new_rect2 = figure::fig_factory::make_rect(200.f, 200.f, 100.f, 100.f, color(0.f, 1.f, 0.f, 1.f));
    auto *new_rect3 = figure::fig_factory::make_rect(300.f, 300.f, 100.f, 100.f, color(0.f, 0.f, 1.f, 1.f));

    figure::fig_factory::delete_fig(new_rect1);
}
