(* CS 431
** Bounce
** Language: Free Pascal
** Compiler fpc
*)

program bounce;
uses Crt;
var
	velocity, x, i : integer;

begin
	writeln('Initial velocity?');
	readln(velocity);
	
	x := 0;
	while (x <> 0) or (velocity <> 0) do
	begin
		for i := 0 to x do
		begin
			write(' ');
		end;
		
		if velocity > 0 then
			writeln('>');
		if velocity < 0 then
			writeln('<');
		if velocity = 0 then
			writeln('v');
		
		x := x + velocity;
		if x <= 0 then
			velocity := -velocity;
		
		velocity := velocity - 1;
	
		Delay(35);
	end;
	writeln('<');
end.

procedure Delay(	
  MS: Word
);