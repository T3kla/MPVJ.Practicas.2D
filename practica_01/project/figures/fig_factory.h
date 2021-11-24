#pragma once

#include "fig.h"
#include "rect.h"
#include <vector>

namespace figure
{

class fig_factory
{
  private:                                     // SINGLETON
    fig_factory();                             //
    static fig_factory instance;               //
  public:                                      //
    fig_factory(const fig_factory &) = delete; //
    static fig_factory &get();                 //

  private:
    std::vector<fig *> m_figures = std::vector<fig *>();

  public:
    static const std::vector<fig *> *get_figures();
    static rect *make_rect(float x, float y, float w, float h, color color);
    static bool delete_fig(fig *);
};

} // namespace figure
