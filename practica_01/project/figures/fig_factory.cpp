#include "fig_factory.h"

namespace figure
{

fig_factory fig_factory::instance;

fig_factory::fig_factory()
{
}

fig_factory &fig_factory::get()
{
    return instance;
}

const std::vector<fig *> *fig_factory::get_figures()
{
    return &get().m_figures;
}

rect *fig_factory::make_rect(float x, float y, float w, float h, color color)
{
    auto *new_rect = new rect(x, y, w, h, color);
    get().m_figures.push_back(new_rect);
    return new_rect;
}

bool fig_factory::delete_fig(fig *fig)
{
    auto &figs = get().m_figures;

    auto old_size = figs.size();
    auto it = std::find(figs.begin(), figs.end(), fig);
    get().m_figures.erase(it);

    if (old_size < figs.size())
        return true;
    else
        return false;
}

} // namespace figure
