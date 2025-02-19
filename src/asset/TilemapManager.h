#ifndef TILEMAP_MANAGER_H
#define TILEMAP_MANAGER_H

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "ResourceManager.h"
#include "render/SpriteRenderer.h"
#include "game/GameObject.h"

/**
 * @brief Manages a tilemap and its rendering, providing support for loading and rendering
 * tiles from a texture atlas.
 */
class TilemapManager {
public:
    /**
     * @brief Represents a single tile in the tilemap.
     */
    struct Tile {
        glm::vec2 Position;       ///< The position of the tile in the world.
        glm::vec2 Size;           ///< The size of the tile in the world.
        glm::vec2 TextureOffset;  ///< Texture UV offset.
        glm::vec2 TextureSize;    ///< Size of the texture region.
        unsigned int TileID;
        bool IsSolid;             ///< Indicates if the tile is solid.
    };
    std::vector<Tile> tiles;            ///< Vector storing tile data.

    /**
     * @brief Constructs the TilemapManager with a given texture path and grid size.
     * @param texturePath Path to the texture atlas.
     * @param tilesAcross Number of tiles across the atlas.
     * @param tilesDown Number of tiles down the atlas.
     */
    TilemapManager(const std::string& texturePath, unsigned int tilesAcross, unsigned int tilesDown);
    TilemapManager(const std::string& texturePath, const std::string& bgTexturePath, unsigned int tilesAcross, unsigned int tilesDown);
    TilemapManager(Texture2D& tex, unsigned int tilesAcross, unsigned int tilesDown);
    /**
     * @brief Loads a tilemap configuration from tile data.
     * @param tileData 2D vector containing tile indices.
     * @param levelWidth Width of the tilemap in world units.
     * @param levelHeight Height of the tilemap in world units.
     */
    void LoadTilemap(const std::vector<std::vector<unsigned int>>& tileData, unsigned int levelWidth, unsigned int levelHeight);
    void LoadTilemap(glm::vec2 dim);

    /**
     * @brief Draws the tilemap using the specified renderer.
     * @param renderer SpriteRenderer used for drawing.
     */
    void Draw(SpriteRenderer& renderer);
    void DrawPlayer(SpriteRenderer& renderer, glm::vec2 pos, glm::vec2 size, int tile);
    void DrawBackground(SpriteRenderer& renderer, int width, int height);

protected:
    std::string texturePath;            ///< Path to the texture atlas.
    unsigned int tilesAcross, tilesDown; ///< Number of tiles across and down the atlas.
    std::shared_ptr<Texture2D> texture; ///< Shared pointer to the texture resource.
    std::shared_ptr<Texture2D> bgTexture;
};

#endif // TILEMAP_MANAGER_H
