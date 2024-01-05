#include "application.hpp"
#include <iostream>

Application::Application() {
    init_SDL();
    init_SDL_Image();
}

Application::~Application() {}

void Application::init_SDL_Image() {
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        printf("Failed to initialise SDL_Image: %s\n", SDL_GetError());
        exit(1);
    }
}

void Application::init_SDL() {
    int renderer_Flags = SDL_RENDERER_ACCELERATED;
    int window_Flags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialise. SDL Error: %s\n", SDL_GetError());
        exit(1);
    }

    m_window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, window_Flags);

    if (!m_window) {
        printf("failed to open %d x %d SDL window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    m_renderer = SDL_CreateRenderer(m_window, -1, renderer_Flags);

    if (!m_renderer) {
        printf("Failed to create SDL renderer: %s", SDL_GetError());
        exit(1);
    }
}

void Application::handle_Input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                handle_Key_Down(&event.key);
                break;
            case SDL_KEYUP:
                handle_Key_Up(&event.key);
                break;
            default:
                break;
        }
    }
}

void Application::prepare_Scene() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Application::present_Scene() {
    SDL_RenderPresent(m_renderer);
}

SDL_Texture* Application::load_Texture(std::string filename) {
    SDL_Texture* texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading: %s", filename);
    texture = IMG_LoadTexture(m_renderer, filename.c_str());
    return texture;
}

void Application::blit_Texture(SDL_Texture* texture, int x_pos, int y_pos) {
    SDL_Rect destination;
    destination.x = x_pos;
    destination.y = y_pos;

    if (SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h) < 0) {
        printf("Failed to query texture: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(m_renderer, texture, NULL, &destination) < 0) {
        printf("Failed to render copy: %s", SDL_GetError());
    }
}

SDL_Renderer* Application::get_SDL_Renderer() {
    return this->m_renderer;
}

void Application::handle_Key_Down(SDL_KeyboardEvent* keyboard_event) {
    if (keyboard_event->repeat == 0) {
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_W) {
            m_player_movement_direction = Player_Movement_Direction::UP;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_S) {
            m_player_movement_direction = Player_Movement_Direction::DOWN;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_A) {
            m_player_movement_direction = Player_Movement_Direction::LEFT;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_D) {
            m_player_movement_direction = Player_Movement_Direction::RIGHT;
        }
    }
}

void Application::handle_Key_Up(SDL_KeyboardEvent* keyboard_event) {
    if (keyboard_event->repeat == 0) {
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_W) {
            m_player_movement_direction = Player_Movement_Direction::NONE;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_S) {
            m_player_movement_direction = Player_Movement_Direction::NONE;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_A) {
            m_player_movement_direction = Player_Movement_Direction::NONE;
        }
        if (keyboard_event->keysym.scancode == SDL_SCANCODE_D) {
            m_player_movement_direction = Player_Movement_Direction::NONE;
        }
    }
}

Player_Movement_Direction Application::get_Player_Movement_Direction() {
    return m_player_movement_direction;
}