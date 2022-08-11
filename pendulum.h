#include <SDL2/SDL.h>
class Pendulum {
    public:
        Pendulum(int base_mass, int base_length, float base_angle, float base_vel, float base_acc, int max_width, int max_height, SDL_Renderer*& render);
        void set_gravity(float g);
        void set_mass(float m);
        void set_angle(float a);
        void set_vel(float v);
        void set_length(int l);
        void set_renderer( SDL_Renderer*& render );
        void draw_pendulum();

    private:
        void create_bob();
        void update_pendulum();
        float x = 0;
        float y = 0;
        int mass = 0;
        int length = 0;
        float angle = 0;
        float vel = 0;
        float acc = 0;
        float gravity = 0;
        int window_width = 0;
        int window_height = 0;
        SDL_Renderer* renderer = NULL;
        SDL_Texture* bob_texture = NULL;
        SDL_Rect bob_rect;

};
