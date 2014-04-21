#ifndef AVALON_GAMECENTER_H
#define AVALON_GAMECENTER_H

class GameCenter
{
public:
    GameCenter(){};
    ~GameCenter(){};
    
    void login();

    bool showAchievements();
    void postAchievement(const char* idName, int percentComplete);
    void clearAllAchievements();

    bool showScores();
    void postScore(const char* idName, int score);
    void clearAllScores();

#if 0 //AVALON_PLATFORM_IS_ANDROID_GOOGLE
    void signIn();
    void signOut();
    bool isSignedIn();
#endif
};

#endif /* AVALON_GAMECENTER_H */
