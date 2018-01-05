library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity beeper_signal is

	port
	(
		clk : in std_logic;
		q : out std_logic;
		K : in std_logic_vector(31 downto 0)
	);
end entity;


architecture rtl of beeper_signal is
begin
	process(clk, K)
		variable cnt : unsigned(31 downto 0);
	begin
		if(rising_edge(clk)) then
			cnt := cnt + unsigned(K);
			q <= cnt(31);
		end if;
	end process;
end rtl;