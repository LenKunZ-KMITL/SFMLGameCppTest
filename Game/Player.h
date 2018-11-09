#pragma once

#include <iostream>
#include <fstream>
using namespace std;
class Player
{
    public:
        /*********************************************
        float bottom , left , right , top ;
        void update ()
        {
                bottom = //sprite.getPosition().y+sprite.getSize().y;
                left = //sprite.getPosition().x ;
                right = //sprite.getPosition().x + sprite.getSize().x;
                top = //sprite.getPosition().y;
        }
        *********************************************/
        static const string FILE_BASE_PATH;
        static const string FILE_EXT;

        static const long SCORE_MIN;
        static const long SCORE_MAX;
        static const long DEFAULT_SCORE;

        Player(string name);

        string GetName();

        long GetScore();
        void SetScore(long score);
        void AddScore(long score);

        long GetMaxScore();
        void ResetScore();
        bool IsNewMaxScore();

        void Save();

    protected:

    private:
        void SetMaxScore(long score);
        void ResetMaxScoreMark();

        string GetFilePath();

        bool ReadFromSave();
        string m_Name;
        long m_Score;
        long m_MaxScore;

        bool m_MaxScoreMark = false;
};

const string Player::FILE_BASE_PATH = "player";
const string Player::FILE_EXT = ".txt";

const long Player::SCORE_MIN = 0;
const long Player::SCORE_MAX = -1;

const long Player::DEFAULT_SCORE = 1500;

