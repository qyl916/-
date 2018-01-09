-- Quartus II VHDL Template
-- Four-State Mealy State Machine

-- A Mealy machine has outputs that depend on both the state and
-- the inputs.	When the inputs change, the outputs are updated
-- immediately, without waiting for a clock edge.  The outputs
-- can be written more than once per state or per clock cycle.

library ieee;
use ieee.std_logic_1164.all;

entity state_machine is

	port
	(
		clk    : in	std_logic;
		keyin	 : in	std_logic;
		cnt    : in std_logic;
		reset	 : in	std_logic;
		keyout : out std_logic;
		cnten  : out std_logic;
		delay  : out std_logic
	);

end entity;

architecture rtl of state_machine is

	-- Build an enumerated type for the state machine
	type state_type is (s0, s1, s2, s3, s4, s5);

	-- Register to hold the current state
	signal state : state_type;

begin

	process (clk, reset)
	begin

		if reset = '1' then
			state <= s0;

		elsif (rising_edge(clk)) then

			-- Determine the next state synchronously, based on
			-- the current state and the input
			case state is
				when s0=>
					if keyin = '1' then
						state <= s1;
					else
						state <= s0;
					end if;
				when s1=>
					if cnt = '1' then
						state <= s2;
					else
						state <= s1;
					end if;
				when s2=>
					if keyin = '1' then
						state <= s3;
					else
						state <= s0;
					end if;
				when s3=>
					if keyin = '1' then
						state <= s3;
					else
						state <= s4;
					end if;
				when s4=>
					if cnt = '1' then
						state <= s5;
					else
						state <= s4;
					end if;
				when s5=>
					if keyin = '1' then
						state <= s3;
					else
						state <= s0;
					end if;
			end case;

		end if;
	end process;

	-- Determine the output based only on the current state
	-- and the input (do not wait for a clock edge).
	process (state, keyin)
	begin
			case state is
				when s0=>
					keyout <= '0';
					cnten <= '0';
					delay <= '0';
				when s1=>
					keyout <= '0';
					cnten <= '1';
					delay <= '1';
				when s2=>
					cnten <= '0';
					delay <= '1';
					if keyin = '1' then
						keyout <= '1';
					else
						keyout <= '0';
					end if;
				when s3=>
					keyout <= '1';
					cnten <= '0';
					delay <= '0';
				when s4=>
					keyout <= '1';
					cnten <= '1';
					delay <= '0';
				when s5=>
					cnten <= '0';
					delay <= '0';
					if keyin = '1' then
						keyout <= '1';
					else
						keyout <= '0';
					end if;		
			end case;
	end process;

end rtl;
