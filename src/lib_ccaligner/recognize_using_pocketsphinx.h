/*
 * Author   : Saurabh Shrivastava
 * Email    : saurabh.shrivastava54@gmail.com
 * Link     : https://github.com/saurabhshri
*/

#ifndef CCALIGNER_RECOGNIZE_USING_POCKETSPHINX_H
#define CCALIGNER_RECOGNIZE_USING_POCKETSPHINX_H

#include "srtparser.h"
#include "read_wav_file.h"
#include "pocketsphinx.h"
#include "grammar_tools.h"
#include "generate_approx_timestamp.h"
#include "commons.h"
#include "params.h"

int levenshtein_distance(const std::string& firstWord, const std::string& secondWord);

class PocketsphinxAligner
{
private:
    std::string _audioFileName, _subtitleFileName;          //input and output filenames
    std::vector<int16_t> _samples;
    std::vector <SubtitleItem*> _subtitles;
    Params * _parameters;

    std::string _modelPath, _lmPath, _dictPath, _fsgPath, _logPath, _phoneticlmPath, _phonemeLogPath;
    long int _audioWindow, _sampleWindow, _searchWindow;

    ps_decoder_t * _psWordDecoder, * _psPhonemeDecoder;
    cmd_ln_t * _configWord, * _configPhoneme;
    char const * _hypWord, * _hypPhoneme;
    int _rvWord, _rvPhoneme;
    int32 _scoreWord, _scorePhoneme;

    bool processFiles();
    bool printWordTimes(cmd_ln_t *config, ps_decoder_t *ps);
    bool printRecognisedWordAsSRT(cmd_ln_t *config, ps_decoder_t *ps);
    recognisedBlock findAndSetWordTimes(cmd_ln_t *config, ps_decoder_t *ps, SubtitleItem *sub);
    recognisedBlock findAndSetPhonemeTimes(cmd_ln_t *config, ps_decoder_t *ps, SubtitleItem *sub);
    bool reInitDecoder(cmd_ln_t *config, ps_decoder_t *ps);
    bool initPhonemeDecoder(std::string phoneticlmPath, std::string phonemeLogPath);

public:
    PocketsphinxAligner(Params * parameters);
    bool initDecoder(std::string modelPath, std::string lmPath, std::string dictPath, std::string fsgPath, std::string logPath);
    bool generateGrammar(grammarName name);
    bool recognise(outputOptions printOption);
    bool alignWithFSG();
    bool align();
    bool recognisePhonemes(const int16_t *sample, int readLimit, SubtitleItem *sub);
    bool transcribe();
    ~PocketsphinxAligner();

};

#endif //CCALIGNER_RECOGNIZE_USING_POCKETSPHINX_H
