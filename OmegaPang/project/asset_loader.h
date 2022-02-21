#pragma once

class AssetLoader
{
    static AssetLoader Instance;

  private:
    AssetLoader() = default;
    AssetLoader(const AssetLoader &) = delete;

  public:
    static void LoadAssets();
    static void UnloadAssets();
};
