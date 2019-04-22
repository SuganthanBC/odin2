/*
  ==============================================================================

    ModMatrix.cpp
    Created: 20 Apr 2019 5:04:47pm
    Author:  frot

  ==============================================================================
*/

#include "ModMatrix.h"

void ModMatrixRow::setSourcesAndDestinations(ModSources *p_source,
                                             ModDestinations *p_destination) {
  m_sources = p_source;
  m_destinations = p_destination;
}

void ModMatrixRow::applyModulation() {
  // poly destination -> 12 modulations
  if (m_destination_poly) {
    for (int voice = 0; voice < VOICES; ++voice) {
      if (m_scale) {
        *(m_destination_value[voice]) +=
            (*m_source_value[voice]) * m_mod_amount *
            (1 + (*m_scale_value[voice] - 1) * m_scale_amount);
      } else {
        *(m_destination_value[voice]) +=
            (*m_source_value[voice]) * m_mod_amount;
      }
    }
  }
}

void ModMatrixRow::setModSource(int p_source) {

  for(int voice = 0;  voice < VOICES; ++voice){
    m_source_value[voice] = &(m_sources->voice[voice].adsr[3]);
  }


  m_source = p_source;
  m_active = (m_source && m_destination);
}

void ModMatrixRow::setModDestination(int p_destination) {


  for(int voice = 0;  voice < VOICES; ++voice){
    m_destination_value[voice] = &(m_destinations->voice[voice].osc[0].pitch_exponential);
  }
  m_destination_poly = true;


  m_destination = p_destination;
  m_active = (m_source && m_destination);
}

void ModMatrixRow::setModScale(int p_scale) { m_scale = p_scale; }

//=========================================================
//=================== MODMATRIX ===========================
//=========================================================


void ModMatrix::applyModulation() {
  for (int row = 0; row < MODMATRIX_ROWS; ++row) {
    if (m_row[row]) {
      m_row[row].applyModulation();
    }
  }
}

void ModMatrix::setSourcesAndDestinations(ModSources *p_sources,
                                          ModDestinations *p_destinations) {
  for (int row = 0; row < MODMATRIX_ROWS; ++row) {
    m_row[row].setSourcesAndDestinations(p_sources, p_destinations);
  }
  m_sources = p_sources;
  m_destinations = p_destinations;
  zeroAllDestinations();
  zeroAllSources();
}

// ModMatrix::ModMatrix(ModSources *p_sources, ModDestinations *p_destinations){
//  for (int row = 0; row < MODMATRIX_ROWS; ++row) {
//    m_row[row].setSourcesAndDestinations(p_sources, p_destinations);
//  }
//}

void ModMatrix::setModSource(int p_row, int p_source) {
  m_row[p_row].setModSource(p_source);
}

void ModMatrix::setModDestination(int p_row, int p_destination) {
  m_row[p_row].setModDestination(p_destination);
}

void ModMatrix::setModScale(int p_row, int p_scale) {
  m_row[p_row].setModScale(p_scale);
}

void ModMatrix::setModAmount(int p_row, float p_mod_amount) {
  m_row[p_row].setModAmount(p_mod_amount);
}

void ModMatrix::setScaleAmount(int p_row, float p_scale_amount) {
  m_row[p_row].setScaleAmount(p_scale_amount);
}

void ModMatrix::zeroAllSources() {
  memset(m_sources, 0 , sizeof(ModSources));
}

void ModMatrix::zeroAllDestinations() {
  memset(m_destinations, 0 , sizeof(ModDestinations));  
}