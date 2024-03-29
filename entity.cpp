#include "entity.hpp"

Entity::Entity() {}

Entity::Entity(SDL_Renderer* sdl_renderer) : m_renderer(sdl_renderer) {
    m_x_pos = PLAYER_START_X;
    m_y_pos = PLAYER_START_Y;
    m_facing = Facing_Direction::FACE_RIGHT;
}

Entity::~Entity() {}

SDL_Texture* Entity::load_Texture(std::string filename) {
    SDL_Texture* texture;
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    std::cout << "Loaded texture of file: " << filename << " with address: " << texture << std::endl;
    return texture;
}

void Entity::blit_Texture(int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    //std::cout << "Current blit texture is: " << m_texture << std::endl;
    //std::cout << "Trying to blit texture to renderer at: " << m_renderer << std::endl;

    if (SDL_QueryTexture(m_texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture of entity: %s", SDL_GetError());
        std::cout << "Texture is: " << m_texture << std::endl;
    }

    if (m_facing == Facing_Direction::FACE_LEFT) {
        if (SDL_RenderCopyEx(m_renderer, m_texture, NULL, &destination, 0, NULL, SDL_FLIP_HORIZONTAL) < 0) {
            printf("Failed to render copy of flipped entity: %s", SDL_GetError());
        }
    }
    else {
        if (SDL_RenderCopy(m_renderer, m_texture, NULL, &destination) < 0) {
            printf("Failed to render copy of entity: %s", SDL_GetError());
        }
    }
}

void Entity::move_Entity_Horizontal(int dx) {
    m_x_pos += dx;
}

void Entity::move_Entity_Vertical(int dy) {
    m_y_pos += dy;
}

int Entity::get_Entity_x_pos() {
    return m_x_pos;
}

int Entity::get_Entity_y_pos() {
    return m_y_pos;
}

void Entity::set_Entity_Facing(Facing_Direction facing) {
    m_facing = facing;
}