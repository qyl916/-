library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity beeper_controller is
	
	generic
	(
		DIV_FACTOR : natural := 50000
	);

	port
	(
		clk		 : in	 std_logic;
		mode		 : in  std_logic;
		sel		 : in  std_logic;
		data		 : in  std_logic_vector(7 downto 0);
		en			 : in  std_logic;
		beep		 : out std_logic;
		sound		 : out std_logic_vector(7 downto 0)
	);

end entity;

architecture rtl of beeper_controller is
	signal en_counter : std_logic;
	signal l_curr : std_logic_vector(7 downto 0);
	signal l_data : std_logic_vector(7 downto 0);
	signal s_data : std_logic_vector(7 downto 0);
begin	
	process(en)
	begin
		if (falling_edge(en)) then
			if mode = '0' and sel = '0' then
				s_data <= data;
			elsif mode = '0' and sel = '1' then
				l_data <= data;
			elsif mode = '1' and sel = '0' then
				sound <= s_data;
				l_curr <= l_data;
				en_counter <= '1';
			elsif mode = '1' and sel = '1' then
				en_counter <= '0';
			end if;
		end if;
	end process;
	
	process(clk, en_counter, l_curr)
		variable cnt1 : integer range 0 to 255 := 0;
		variable cnt2 : integer range 0 to 65535 := 0;
		variable max : integer range 0 to 255 ;
	begin
		max := to_integer(unsigned(l_curr));
		if(rising_edge(clk)) then
			if(en_counter = '1') then
				if cnt1 = 0 then
					beep <= '1';
				end if;
				cnt2 := cnt2 + 1;
				if cnt2 >= DIV_FACTOR then
					cnt2 := 0;
					if max = 0 or (cnt1 < max) then
						cnt1 := cnt1 + 1;
					elsif cnt1 >= max then
						beep <= '0';
					end if;
				end if;
			else
				cnt1 := 0;
				cnt2 := 0;
				beep <= '0';
			end if;
		end if;
	end process;
end rtl;
