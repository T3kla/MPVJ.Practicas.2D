#pragma once

struct AudioFilter
{

    ALuint id;

    AudioFilter(ALuint id = 0)
        : id(id){
              // alGenEffects(1, &id);
          };

    ~AudioFilter(){
        // alDeleteEffects(1, &id);
    };
};
