//
// Created by Mike Mitterer on 22.07.16.
//

#ifndef RASPIHELLOWORLD_GPIO_H
#define RASPIHELLOWORLD_GPIO_H

#include <RF24/nRF24L01.h>
#include <RF24/RF24.h>
#include <functional>

/*! was 1 - This means pin HIGH, true, 3.3volts on a pin. */
#undef HIGH
/*! was 0 - This means pin LOW, false, 0volts on a pin. */
#undef LOW

/**
 * Example GPIO.h file
 *
 * @defgroup GPIO GPIO Example
 *
 * See RF24_arch_config.h for additional information
 * @{
 */

namespace mm {

    namespace gpio {

        class Board {
        private:
            bool initialized = false;

        public:

            /// Necessary!!!!
            /// Returns true if it succeeds - otherwaise it returns false
            bool init() {
                if(!initialized) {
                    initialized = bcm2835_init() == 1;
                }
                return  initialized;
            }

        ~Board() {
            bcm2835_close();
        }

        private:

        };

        class Pin {
        public:
            enum class Direction {
                INPUT, OUTPUT, UNDEFINED
            };

            enum class InputState {
                /*! This means pin HIGH, true, 3.3volts on a pin. */
                        HIGH,
                /*! This means pin LOW, false, 0volts on a pin. */
                        LOW
            };

            enum class OutputState { ON, OFF};

        private:
            const uint8_t pin;
            Direction direction = Direction::UNDEFINED;
            std::function<void (Pin& pin)> closing = [] (Pin& pin) { printf("Closing function!\n"); };

        public:

            Pin(const uint8_t pinParam) : pin{pinParam} {
            }

            Pin(const uint8_t pinParam,std::function<void (Pin& pin)> closing) : pin{pinParam} {
                mode(direction);
                this->closing = closing;
            }

            ~Pin() {
                closing(*this);
            }

            const Direction& mode(const Direction& direction) {
                if(direction == Direction::INPUT) {
                    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
                } else {
                    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
                }
                this->direction = direction;
                return this->direction;
            }

            InputState read() {
                if(direction != Direction::INPUT) {
                    direction = mode(Direction::INPUT);
                }
                return bcm2835_gpio_lev(pin) == 0 ? InputState::LOW : InputState::HIGH;
            }

            void write(const OutputState state) {
                if(direction != Direction::OUTPUT) {
                    direction = mode(Direction::OUTPUT);
                }
                bcm2835_gpio_write(pin, (uint8_t) (state == OutputState::ON ? 1 : 0));
            }
        };
    }

}

#endif //RASPIHELLOWORLD_GPIO_H
