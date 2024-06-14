#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cctype>
#include <iterator>
#include <algorithm>

using namespace std;

// Struct to store sequences and offsets
struct SequenceOffsetPair
{
    SequenceOffsetPair(string sequence, size_t offset) : m_sequence(sequence), m_offset(offset) {}

    string m_sequence;
    size_t m_offset;
};

// Table Data Structure Declaration
class HashTable
{
public:
    HashTable()
    {
        m_hashTable.resize(m_buckets);
    }

    void insert(string sequence, size_t offset)
    {
        size_t index = hash<string>()(sequence) % m_buckets;
        SequenceOffsetPair sequenceOffsetPair(sequence, offset);
        m_hashTable.at(index).push_back(sequenceOffsetPair);
    }

    bool contains(string sequence) const
    {
        size_t index = hash<string>()(sequence) % m_buckets;

        for (const auto &it : m_hashTable.at(index))
        {
            if (it.m_sequence == sequence)
            {
                return true;
            }
        }

        return false;
    }

    const list<SequenceOffsetPair> &get(string sequence) const
    {
        size_t index = hash<string>()(sequence) % m_buckets;
        return m_hashTable.at(index);
    }

private:
    static const size_t m_buckets = 10007;
    vector<list<SequenceOffsetPair> > m_hashTable;
};

// Given by spec
bool getInt(istream &inf, int &n)
{
    char ch;
    if (!inf.get(ch) || !isascii(ch) || !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

// Given by spec
bool getCommand(istream &inf, char &cmd, char &delim, int &length, int &offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x'; // signals end of file
        return true;
    }
    switch (cmd)
    {
    case '+':
        return inf.get(delim).good();
    case '#':
    {
        char ch;
        return getInt(inf, offset) && inf.get(ch) && ch == ',' && getInt(inf, length);
    }
    case '\r':
    case '\n':
        return true;
    }
    return false;
}

// Helper function to see if a character is in a string
bool contains(string sequence, char find)
{
    for (char c : sequence)
    {
        if (c == find)
        {
            return true;
        }
    }

    return false;
}

// Helper function to decide delimiter
char decide(string addition)
{
    char check = '!';

    while (contains(addition, check % 128))
    {
        check++;
    }

    return check;
}

void createRevision(istream &fold, istream &fnew, ostream &frevision)
{
    // 1. Read in the entire contents of the old file into a string. Read the entire contents of the new file into another string.
    char read;
    string oldFile, newFile;

    while (fold.get(read))
    {
        oldFile += read;
    }

    while (fnew.get(read))
    {
        newFile += read;
    }

    // 2. For all consecutive N-character sequences in the old file's string, insert that N-character sequence and the offset F where it was found in the old file's string, into a table (e.g. hash table or binary search tree). You might use 8 for N, or maybe 16.
    const int N = 8;

    if (newFile.size() < N || oldFile.size() < N)
    {
        frevision << '+' << newFile.size() << '/' << newFile;
        return;
    }

    HashTable sequenceOffsetPairs;

    for (size_t F = 0; F + N <= oldFile.size(); F++)
    {
        sequenceOffsetPairs.insert(oldFile.substr(F, N), F);
    }

    // 3. Once you have filled up your table with all N-byte sequences from the source file, start processing the new file's string, starting from offset j=0, until j reaches the end of the string.
    size_t j = 0;

    while (j < newFile.size())
    {
        size_t bestL = 0;
        size_t bestF = 0;

        if (j + N <= newFile.size())
        {
            // a. Look up the N-byte sequence which starts at offset j ([j,j+N-1]) in the new file's string in the table you created from the old file's string.
            string NByteSequence = newFile.substr(j, N);
            // b. If you find this sequence in the table, you know that that sequence is present in both the old and new versions of the file.
            if (sequenceOffsetPairs.contains(NByteSequence))
            {
                for (SequenceOffsetPair sequenceOffsetPair : sequenceOffsetPairs.get(NByteSequence))
                {
                    if (sequenceOffsetPair.m_sequence == NByteSequence)
                    {
                        size_t F = sequenceOffsetPair.m_offset;
                        size_t L = N;
                        // i. Determine how long the match goes on (it might be just N bytes long, or it might extend past the first N matching bytes to be many bytes longer).
                        while (j + L < newFile.size() && F + L < oldFile.size() && newFile[j + L] == oldFile[F + L])
                        {
                            L++;
                        }

                        if (L > bestL)
                        {
                            bestL = L;
                            bestF = F;
                        }
                    }
                }
            }
        }

        // ii. Once you have determined how long the match is (call this L), write a Copy instruction to the revision file to copy L bytes from offset F from the source file.
        if (bestL > 0)
        {
            frevision << "#" << bestF << "," << bestL;
            // iii. Go back to step 3a, continuing at offset j = j + L in the new file's string.
            j += bestL;
        }
        // c. If you don't find the current sequence (new file's string [j,j+N-1]) in the table you created, you know that the first version of the file doesn't contain the current N byte sequence.
        else
        {
            // ii. Increment j by one to continue past the character used in the add instruction.
            size_t start = j;

            while (j < newFile.size() && (j + N > newFile.size() || !sequenceOffsetPairs.contains(newFile.substr(j, N))))
            {
                j++;
            }
            // i. Write an instruction to the revision file to Add the current character.
            string addition = newFile.substr(start, j - start);
            char delimiter = decide(addition);
            frevision << "+" << delimiter << addition << delimiter;
        }
        // iii. Go back to step 3a, where we'll try to find the next N-byte sequence in our table.
    }
}

bool revise(istream &fold, istream &frevision, ostream &fnew)
{
    // Read the old file
    char read;
    string oldFile;

    while (fold.get(read))
    {
        oldFile += read;
    }

    ostringstream newFile;
    char cmd, delim;
    int length = 0, offset = 0;

    while (getCommand(frevision, cmd, delim, length, offset))
    {
        // Invalid
        if (cmd == 'x')
        {
            break;
        }

        // Add
        if (cmd == '+')
        {
            string addition;
            char ch;

            while (frevision.get(ch) && ch != delim)
            {
                addition += ch;
            }

            if (ch != delim)
            {
                return false;
            }

            newFile << addition;
        }
        // Copy
        else if (cmd == '#')
        {
            if (offset < 0 || offset + length > oldFile.size())
            {
                return false; 
            }

            newFile << oldFile.substr(offset, length);
        }
        else if (cmd == '\n' || cmd == '\r')
        {
            continue; 
        }
        else
        {
            return false;
        }
    }

    fnew << newFile.str();
    return true;
}

int main()
{

}