#include <iostream>
#include <tuple>
#include <functional>
#include <string>

template <typename... Handlers>
class EventHandler
{
public:
    EventHandler(Handlers const&... handlers) : m_handlers{handlers...}
    {}

    struct Event
    {
        int eventType;
        std::string data;
        int priority;
    };

    /*template <size_t HandlerType, typename Handler>
    void SetHandler(Handler& handler)
    {
        std::get<HandlerType>(m_handlers) = handler;
    }
*/
    void HandleEvent(Event const& event)
    {

        switch (event.eventType)
        {
            case 0:
                std::get<0>(m_handlers)(event.data);
                break;
            case 1:
                std::get<1>(m_handlers)(event.data.length(), event.priority);
                break;
            default:
                std::cerr << "Unsupported event type\n";
        }
    }

    private:
        std::tuple<Handlers const&...> m_handlers;
};


int main()
{
    using Callback1 = std::function<void(std::string)>;
    using Callback2 = std::function<void(int, int)>;

    auto callback1 = [](std::string str)
    { std::cout << "Callback1 " << str << "\n";};

    auto callback2 = [](int x, int y)
    { std::cout << "Callback2 " << x << " " << y << "\n";};

    using MyHandler = EventHandler<Callback1, Callback2>;
    MyHandler handler(callback1, callback2);

    MyHandler::Event event{0, "Test String", 42};
    handler.HandleEvent(event);
    return 0;
};
