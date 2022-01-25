

#ifndef SPACESHOOTER_CHARACTERRANGE_H
#define SPACESHOOTER_CHARACTERRANGE_H


struct CharacterRange
{
    CharacterRange(unsigned int characterCodeFrom, unsigned int characterCodeTo)
    {
        m_characterCodeFrom = characterCodeFrom;
        m_characterCodeTo = characterCodeTo;
    }

    unsigned int m_characterCodeFrom;
    unsigned int m_characterCodeTo;
};

#endif //SPACESHOOTER_CHARACTERRANGE_H
