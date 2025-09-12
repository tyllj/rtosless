#ifndef RTOSLESS_SAMPLE_BUFFER_H
#define RTOSLESS_SAMPLE_BUFFER_H

#include <stdint.h>
#include <stddef.h>

#if defined(__AVR__)
#include <util/atomic.h>
#define RL_CRITICAL_SECTION_AVR_ONLY ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#else
#define RL_CRITICAL_SECTION_AVR_ONLY if (true)
#endif

namespace rl {

    template<typename t_sample, size_t n_samples>
    class sample_buffer_t {
    private:
        t_sample buffer[n_samples];
        volatile size_t head = 0;  // next write
        volatile size_t tail = 0;  // next read

        static size_t next(size_t index) {
            return (index + 1) % n_samples;
        }

    public:
        size_t get_capacity() const {
            return n_samples;
        }

        size_t get_count() const {
            RL_CRITICAL_SECTION_AVR_ONLY {
                size_t h = head;
                size_t t = tail;
                return (h >= t) ? (h - t) : (n_samples + h - t);
            }
        }

        t_sample get_avg(size_t n = n_samples) const {
            size_t count;
            RL_CRITICAL_SECTION_AVR_ONLY {
                count = get_count();
            }
            if (count == 0) return 0;

            size_t samples = (n < count) ? n : count;
            t_sample sum = 0;
            for (size_t i = 0; i < samples; ++i) {
                sum += peek(i);
            }
            return sum / samples;
        }

        t_sample peek(size_t n) const {
            size_t count;
            RL_CRITICAL_SECTION_AVR_ONLY {
                count = get_count();
            }
            if (n >= count) return 0;

            size_t index;
            RL_CRITICAL_SECTION_AVR_ONLY {
                index = (tail + n) % n_samples;
            }
            return buffer[index];
        }

        void push_back(t_sample sample) {
            buffer[head] = sample;
            size_t next_head = next(head);

            RL_CRITICAL_SECTION_AVR_ONLY {
                if (next_head == tail) {
                    tail = next(tail);  // drop oldest
                }
                head = next_head;
            }
        }

        bool try_pop(t_sample* out_sample) {
            RL_CRITICAL_SECTION_AVR_ONLY {
                if (get_count() == 0) return false;
                *out_sample = buffer[tail];
                tail = next(tail);
                return true;
            }
        }
    };

} // namespace rl

#endif // RTOSLESS_SAMPLE_BUFFER_H
