/*
** probable-goggles
** File description:
** IGUI
*/

#ifndef IGUI_HPP_
#define IGUI_HPP_
    class IGUI {
    public:
        virtual ~IGUI() {}

        virtual void init() = 0;
        virtual void draw() = 0;
        virtual int handleInput() = 0;
        virtual void update() = 0;
        virtual void clear() = 0;
        virtual void refresh() = 0;
        virtual void close() = 0;
    };
#endif /* !IATTACKS_HPP_ */
