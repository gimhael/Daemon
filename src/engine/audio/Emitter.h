/*
===========================================================================

daemon gpl source code
copyright (c) 2013 unvanquished developers

this file is part of the daemon gpl source code (daemon source code).

daemon source code is free software: you can redistribute it and/or modify
it under the terms of the gnu general public license as published by
the free software foundation, either version 3 of the license, or
(at your option) any later version.

daemon source code is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  see the
gnu general public license for more details.

you should have received a copy of the gnu general public license
along with daemon source code.  if not, see <http://www.gnu.org/licenses/>.

===========================================================================
*/

#include "ALObjects.h"
#include "Sound.h"
#include "../../common/String.h"

#ifndef AUDIO_EMITTER_H_
#define AUDIO_EMITTER_H_

namespace Audio {

    void InitEmitters();
    void ShutdownEmitters();

    void UpdateEverything();

    Emitter* GetEmitterForEntity(int entityNum);
    Emitter* GetEmitterForPosition(const vec3_t position);
    Emitter* GetLocalEmitter();

    void UpdateEntityPosition(int entityNum, const vec3_t position);
    void UpdateEntityVelocity(int entityNum, const vec3_t velocity);
    void UpdateEntityOcclusion(int entityNum, float ratio);

    class Sound;

    namespace AL {
        class Source;
    }

    class Emitter {
        public:
            Emitter();
            virtual ~Emitter();

            void Update();
            virtual void UpdateSource(AL::Source& source) = 0;
            void SetupSource(AL::Source& source);
            virtual void InternalSetupSource(AL::Source& source) = 0;

            void AddSound(Sound* sound);
            void RemoveSound(Sound* sound);
            bool HasSounds() const;
            const std::vector<Sound*>& GetSounds();

        protected:
            std::vector<Sound*> sounds;

            float targetGain;
            float currentGain;
    };

    class EntityEmitter : public Emitter {
        public:
            EntityEmitter(int entityNum);
            virtual ~EntityEmitter();

            virtual void UpdateSource(AL::Source& source) OVERRIDE;
            virtual void InternalSetupSource(AL::Source& source) OVERRIDE;

        private:
            int entityNum;
    };

    class PositionEmitter : public Emitter {
        public:
            PositionEmitter(const vec3_t position);
            virtual ~PositionEmitter();

            virtual void UpdateSource(AL::Source& source) OVERRIDE;
            virtual void InternalSetupSource(AL::Source& source) OVERRIDE;

            const vec3_t& GetPosition() const;

        private:
            vec3_t position;
    };

    class LocalEmitter: public Emitter {
        public:
            LocalEmitter();
            virtual ~LocalEmitter();

            virtual void UpdateSource(AL::Source& source) OVERRIDE;
            virtual void InternalSetupSource(AL::Source& source) OVERRIDE;
    };

}

#endif //AUDIO_SAMPLE_H_
