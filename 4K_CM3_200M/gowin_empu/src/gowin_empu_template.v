
//sys_clk max 200MHz
//GPIO
//UART0
//Timer0

`resetall

module Gowin_EMPU_Template (
  sys_clk,
  reset_n,
  led,
  uart0_rxd,
  uart0_txd
);

input sys_clk;
input reset_n;

//GPIO
inout led;

//UART0
input uart0_rxd;
output uart0_txd;

wire mclk;              //mcu clock

//MCU system clock = 2000MHz
Gowin_PLLVR u_Gowin_PLLVR(
  .clkout(mclk),            //MCU 200MHz
  .clkin(sys_clk)           //input clkin 50MHz
);

Gowin_EMPU_Top u_Gowin_EMPU_Top (
  .sys_clk(mclk),
  .reset_n(reset_n),
  //GPIO
  .gpio(led),
  //UART0
  .uart0_rxd(uart0_rxd),
  .uart0_txd(uart0_txd)
 );

endmodule