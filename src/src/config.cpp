#include "config.h"
#include "common.h"
#include "POWERMGNT.h"

void
TxConfig::Load()
{
    // Populate the struct from eeprom
    m_eeprom->Get(0, m_config);

    // Check if version number matches
    if (m_config.version != TX_CONFIG_VERSION)
    {
        // If not, revert to defaults for this version
        Serial.println("EEPROM version mismatch! Resetting to defaults...");
        SetDefaults();
    }

    m_modified = false;
}

void
TxConfig::Commit()
{    
    if (!m_modified)
    {
        // No changes
        return;
    }

    // Write the struct to eeprom
    m_eeprom->Put(0, m_config);
    m_eeprom->Commit();

    m_modified = false;
}

// Setters
void
TxConfig::SetRate(uint8_t modelId, uint8_t rate)
{
    if (m_config.model_config[modelId].rate != rate)
    {
        m_config.model_config[modelId].rate = rate;
        m_modified = true;
    }
}

void
TxConfig::SetTlm(uint8_t modelId, uint8_t tlm)
{
    if (m_config.model_config[modelId].tlm != tlm)
    {
        m_config.model_config[modelId].tlm = tlm;
        m_modified = true;
    }
}

void
TxConfig::SetPower(uint8_t modelId, uint8_t power)
{
    if (m_config.model_config[modelId].power != power)
    {
        m_config.model_config[modelId].power = power;
        m_modified = true;
    }
}

void
TxConfig::SetSwitchMode(uint8_t modelId, uint8_t switchMode)
{
    if (m_config.model_config[modelId].switchMode != switchMode)
    {
        m_config.model_config[modelId].switchMode = switchMode;
        m_modified = true;
    }
}

void
TxConfig::SetModelMatch(uint8_t modelId, bool modelMatch)
{
    if (m_config.model_config[modelId].modelMatch != modelMatch)
    {
        m_config.model_config[modelId].modelMatch = modelMatch;
        m_modified = true;
    }
}

void
TxConfig::SetDefaults()
{
    expresslrs_mod_settings_s *const modParams = get_elrs_airRateConfig(RATE_DEFAULT);
    m_config.version = TX_CONFIG_VERSION;
    SetSSID("");
    SetPassword("");
    for (int i=0 ; i<64 ; i++) {
        SetRate(i, modParams->index);
        SetTlm(i, modParams->TLMinterval);
        SetPower(i, DefaultPowerEnum);
        SetSwitchMode(i, 1);
        SetModelMatch(i, false);
    }
    Commit();
}

void
TxConfig::SetStorageProvider(ELRS_EEPROM *eeprom)
{
    if (eeprom)
    {
        m_eeprom = eeprom;
    }
}

void
TxConfig::SetSSID(const char *ssid)
{
    strncpy(m_config.ssid, ssid, sizeof(m_config.ssid)-1);
    m_modified = true;
}

void
TxConfig::SetPassword(const char *password)
{
    strncpy(m_config.password, password, sizeof(m_config.password)-1);
    m_modified = true;
}

/////////////////////////////////////////////////////

void
RxConfig::Load()
{
    // Populate the struct from eeprom
    m_eeprom->Get(0, m_config);

    // Check if version number matches
    if (m_config.version != RX_CONFIG_VERSION)
    {
        // If not, revert to defaults for this version
        Serial.println("EEPROM version mismatch! Resetting to defaults...");
        SetDefaults();
    }

    m_modified = false;
}

void
RxConfig::Commit()
{    
    if (!m_modified)
    {
        // No changes
        return;
    }

    // Write the struct to eeprom
    m_eeprom->Put(0, m_config);
    m_eeprom->Commit();

    m_modified = false;
}

// Setters
void
RxConfig::SetIsBound(bool isBound)
{
    if (m_config.isBound != isBound)
    {
        m_config.isBound = isBound;
        m_modified = true;
    }
}

void
RxConfig::SetUID(uint8_t* uid)
{
    for (uint8_t i = 0; i < UID_LEN; ++i)
    {
        m_config.uid[i] = uid[i];
    }
    m_modified = true;
}

void
RxConfig::SetPowerOnCounter(uint8_t powerOnCounter)
{
    if (m_config.powerOnCounter != powerOnCounter)
    {
        m_config.powerOnCounter = powerOnCounter;
        m_modified = true;
    }
}

void
RxConfig::SetModelId(uint8_t modelId)
{
    if (m_config.modelId != modelId)
    {
        m_config.modelId = modelId;
        m_modified = true;
    }
}

void
RxConfig::SetDefaults()
{
    m_config.version = RX_CONFIG_VERSION;
    SetIsBound(false);
    SetPowerOnCounter(0);
    SetModelId(0xFF);
    SetSSID("");
    SetPassword("");
    Commit();
}

void
RxConfig::SetStorageProvider(ELRS_EEPROM *eeprom)
{
    if (eeprom)
    {
        m_eeprom = eeprom;
    }
}

void
RxConfig::SetSSID(const char *ssid)
{
    strncpy(m_config.ssid, ssid, sizeof(m_config.ssid)-1);
    m_modified = true;
}

void
RxConfig::SetPassword(const char *password)
{
    strncpy(m_config.password, password, sizeof(m_config.password)-1);
    m_modified = true;
}
