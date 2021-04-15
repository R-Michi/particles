#define STB_IMAGE_IMPLEMENTATION // define here to only implement stm once
#include "particles.hpp"
#include "app.hpp"

int main()
{
    particle::application app;
    particle::application::configuration config;

    config.max_particles = 10000;
    config.particle_correct_alpha = false;

    config.fountain_height = 1;
    config.fountain_width = 0.5;
    config.fountain_sweep_steps = 6;

    config.particle_ttl = std::chrono::seconds(5);
    config.particle_gravity = 9.81;
    config.particle_bounce_friction = 0.75;

    config.cam_sensitivity = 0.0002;
    config.cam_speed = 2;
    config.cam_fov = 100;

    omp_set_num_threads(omp_get_max_threads());

    if(app.init(config))
    {
        std::clog << "[main] starting application" << std::endl;
        app.run();
        std::clog << "[main] application ended" << std::endl;
    }
    else
    {
        std::clog << "[main] failed to start application" << std::endl;
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cerr << "[GL ERROR] code: " << (err) << std::endl;
        }
    }


    return 0;
}
