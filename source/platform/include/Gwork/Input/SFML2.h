/*
 *  Gwork
 *  Copyright (c) 2011 Facepunch Studios
 *  Copyright (c) 2013-16 Billy Quith
 *  See license in Gwork.h
 */

#pragma once
#ifndef GWK_INPUT_SFML_H
#define GWK_INPUT_SFML_H

#include <Gwork/Gwork.h>
#include <Gwork/InputEventListener.h>
#include <SFML/Window/Event.hpp>

namespace Gwk
{
    namespace Input
    {
        class SFML
        {
        public:

            SFML()
            :   m_EventListener(NULL)
            ,   m_MouseX(0)
            ,   m_MouseY(0)
            {
            }

            void Initialize(IInputEventListener* c)
            {
                m_EventListener = c;
            }

            unsigned char TranslateKeyCode(int iKeyCode)
            {
                switch (iKeyCode)
                {
                case sf::Keyboard::BackSpace:
                    return Gwk::Key::Backspace;

                case sf::Keyboard::Return:
                    return Gwk::Key::Return;

                case sf::Keyboard::Escape:
                    return Gwk::Key::Escape;

                case sf::Keyboard::Tab:
                    return Gwk::Key::Tab;

                case sf::Keyboard::Space:
                    return Gwk::Key::Space;

                case sf::Keyboard::Up:
                    return Gwk::Key::Up;

                case sf::Keyboard::Down:
                    return Gwk::Key::Down;

                case sf::Keyboard::Left:
                    return Gwk::Key::Left;

                case sf::Keyboard::Right:
                    return Gwk::Key::Right;

                case sf::Keyboard::Home:
                    return Gwk::Key::Home;

                case sf::Keyboard::End:
                    return Gwk::Key::End;

                case sf::Keyboard::Delete:
                    return Gwk::Key::Delete;

                case sf::Keyboard::LControl:
                    return Gwk::Key::Control;

                case sf::Keyboard::LAlt:
                    return Gwk::Key::Alt;

                case sf::Keyboard::LShift:
                    return Gwk::Key::Shift;

                case sf::Keyboard::RControl:
                    return Gwk::Key::Control;

                case sf::Keyboard::RAlt:
                    return Gwk::Key::Alt;

                case sf::Keyboard::RShift:
                    return Gwk::Key::Shift;
                }

                return Gwk::Key::Invalid;
            }

            bool ProcessMessage(const sf::Event& event)
            {
                if (!m_EventListener)
                    return false;

                switch (event.type)
                {
                case sf::Event::MouseMoved:
                    {
                        int dx = event.mouseMove.x-m_MouseX;
                        int dy = event.mouseMove.y-m_MouseY;
                        m_MouseX = event.mouseMove.x;
                        m_MouseY = event.mouseMove.y;
                        return m_EventListener->InputMouseMoved(m_MouseX, m_MouseY, dx, dy);
                    }

                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                    return m_EventListener->InputMouseButton(event.mouseButton.button,
                                                      event.type == sf::Event::MouseButtonPressed);

                case sf::Event::MouseWheelMoved:
                    return m_EventListener->InputMouseWheel(event.mouseWheel.delta*60);

                case sf::Event::TextEntered:
                    return m_EventListener->InputCharacter(event.text.unicode);

                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                    {
                        bool bPressed = (event.type == sf::Event::KeyPressed);
                        char keyCode = event.key.code;
                        bool control = event.key.control;

                        if (control && bPressed && keyCode >= 'a' && keyCode <= 'z')
                            return m_EventListener->InputCharacter(keyCode);

                        unsigned char iKey = TranslateKeyCode(keyCode);
                        return m_EventListener->InputKey(iKey, bPressed);
                    }
                        
                default:
                    ;
                }

                return false;
            }

        protected:

            IInputEventListener *m_EventListener;
            int m_MouseX;
            int m_MouseY;

        };

    }
}
#endif // ifndef GWK_INPUT_SFML_H
