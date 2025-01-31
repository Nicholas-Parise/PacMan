#include <iostream>

   enum class GameStates{
    MENU,
    SETTINGS,
    HELP,
    GAME,
    PAUSE,
    GAMEOVER
    };

class GameStateManager{
    public:
        GameStateManager();
        virtual ~GameStateManager();
        void changeState(GameStates s);
        void increment();
        void reset();
        bool endGame();
        void toString(GameStates s);

        GameStates gState;
        int powerUpTimer;
        int glowTimer;
        int berryTimer;
        int ghostState;
        int gameoverTimer;
        int TitlePacTimer;
        int pauseTimer;

        bool GhostScared;
        bool PacDead;

    protected:

    private:
};
