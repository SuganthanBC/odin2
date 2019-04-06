#define DEBUG_VARIABLES

void OdinAudioProcessor::treeValueChanged(const String &p_ID,
                                          float p_new_value) {

  // create identifier once, then compare it against everything
  Identifier id(p_ID);

#ifdef DEBUG_VARIABLES
  DBG(p_ID + ": " + std::to_string(p_new_value));
#endif

  if (id == m_osc1_analog_wave_identifier) {
    for(int voice = 0; voice < VOICES; ++voice){
      m_voice[voice].analog_osc[0].selectWavetable((int)p_new_value - 1);
    }
  }

}