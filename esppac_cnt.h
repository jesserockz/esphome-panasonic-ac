#include "esphome.h"
#include "esppac.h"

namespace ESPPAC
{
  namespace CNT
  {
    static const ACType TYPE = ACType::CZTACG1;

    static const byte CTRL_HEADER = 0xF0; // The header for control frames
    static const byte POLL_HEADER = 0x70; // The header for the poll command

    static const int POLL_INTERVAL = 5000; // The interval at which to poll the AC

    class PanasonicACCNT : public ESPPAC::PanasonicAC
    {
      public:
        PanasonicACCNT(uart::UARTComponent *uartComponent);

        void control(const climate::ClimateCall &call) override;

        void setup() override;
        void loop() override;

      private:
        byte data[10]; // Stores the data received from the AC
        void handle_poll();

        void send_command(const byte* command, size_t commandLength, CommandType type, byte header);
        void send_packet(byte* packet, size_t packetLength, CommandType type);

        bool verify_packet();
        void handle_packet();

        climate::ClimateMode determine_mode(byte mode);
        std::string determine_fan_speed(byte speed);

        const char* determine_vertical_swing(byte swing);
        const char* determine_horizontal_swing(byte swing);

        climate::ClimatePreset determine_preset(byte preset);
        bool determine_preset_nanoex(byte preset);
        bool determine_mild_dry(byte value);
    };
  }
}