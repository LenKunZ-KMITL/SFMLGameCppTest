#include "Player.h"
#include <fstream>
#include <string>

#include <errno.h>
#include <string.h>

Player::Player(string name)
{
    // Clause guard
    if(name.length() == 0) {
        throw "EINVALID_ARGUMENT name is whitespace";
    }

    ResetScore();

    // Try to read file, or else set default.
    if(!ReadFromSave()) {
        SetMaxScore(GetScore());
        ResetMaxScoreMark();
    }
}

string Player::GetName()
{
    return m_Name;
}

long Player::GetScore()
{
    return m_Score;
}

void Player::SetScore(long score)
{
    if (SCORE_MIN != -1 && score < SCORE_MIN) {
        throw "EOUT_OF_RANGE score is less than " + SCORE_MIN;
    }

    if (SCORE_MAX != -1 && score > SCORE_MAX) {
        throw "EOUT_OF_RANGE score is greater than " + SCORE_MAX;
    }

    m_Score = score;

    if (m_Score > GetMaxScore()) {
        SetMaxScore(m_Score);
    }
}

void Player::AddScore(long pointAdd)
{
    SetScore(pointAdd + GetScore());
}

long Player::GetMaxScore()
{
    return m_MaxScore;
}

void Player::ResetScore()
{
    SetScore(SCORE_MIN != -1 ? SCORE_MIN : 0);
    ResetMaxScoreMark();
}

bool Player::IsNewMaxScore()
{
    return m_MaxScoreMark;
}

void Player::Save()
{
    ofstream playerFile(GetFilePath());

    if(playerFile.good()){
        playerFile << GetMaxScore();
    }else{
        throw string("EIO_ERROR ");
    }
}

void Player::SetMaxScore(long score)
{
    m_MaxScore = score;
    m_MaxScoreMark = true;
}

void Player::ResetMaxScoreMark()
{
    m_MaxScoreMark = false;
}

string Player::GetFilePath() {
    return FILE_BASE_PATH + "/" + GetName() + FILE_EXT;
}

bool Player::ReadFromSave()
{
    ifstream playerFile(GetFilePath());

    if (!playerFile.good()){
        return false;
    }
    if (playerFile.peek() == EOF) {
        return false;
    }

    long maxScore;
    playerFile >> maxScore;

    try {
        SetMaxScore(maxScore);
    } catch(string err) {
        return false;
    }

    playerFile.close();
    return true;
}

