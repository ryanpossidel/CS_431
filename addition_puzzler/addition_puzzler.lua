-- CS 431
-- Addition Puzzler
-- Language: lua
-- Compile: lua filename
-- It can take a while to run because it loops untils it 
-- finds a correct problem
print("How many numbers?")
nums = io.read("*number")
print("How many digits wide?")
width = io.read("*number")
print("How many variables?")
vars = io.read("*number")
print("How many digits revealed?")
revealed = io.read("*number")
print()
-- Gets total number of variables
total_vars = vars + revealed
z = 0
--will infinte loop until a correct problem is found
while(z < 5)
do
	math.randomseed(os.time())
	x = {}
	-- Gets random numbers for the variables
	for i = 1, total_vars do
		x[i] = math.random(0,9)
	end

	y = {}
	-- Makes the numbers
	for i = 1, nums do
		y[i] = x[math.random(1,total_vars)]
		for j = 1, width-1 do
			y[i] = y[i] .. x[math.random(1,total_vars)]
		end
		tonumber(y[i])
	end

	-- Addition
	answer = 0
	for i = 1, nums do 
		answer = answer + y[i]
	end
	answer = tostring(math.floor(answer))

	if(string.len(answer) > width)
	then
		answer = answer:sub(1,-2)
	elseif(string.len(answer) < width)
	then
		for i = 1, width-answer do
			answer = "0" .. answer
		end
	end
	
	--Checks if the answer is correct
	correct = 0
	for i = 1, width do
		compare = string.sub(answer, i, i)
		for j = 1, total_vars do
			x[j] = tostring(x[j])
			if(compare == x[j])
			then
				correct = correct + 1
			end
		end
	end

	--if a correct problem is found it changes the vars to letters
	if(correct == width)
	then
		alphabet = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N",
					"O","P","Q","R","S","T","U","V","W","X","Y","Z" }
		
		variables = {}
		for i = 1, vars do
			variables[i] = x[i]
		end
		
		for i = 1, nums do
			convert = y[i]
			for j = 1, width do
				for n = 1, vars do
					variables[n] = tostring(variables[n])
					if(string.sub(convert,j,j) == variables[n])
					then
						repl = string.sub(convert,j,j)
						convert = string.gsub(convert, repl, alphabet[n])
					end
				end
			end
			print(convert)
		end
		io.write("+")
		
		for i = 1, width do
			io.write("-")
		end
		print()
		for i = 1, width do
			for j = 1, vars do
				variables[j] = tostring(variables[j])
				if(string.sub(answer,i,i) == variables[j])
				then
					repl = string.sub(answer,i,i)
					answer = string.gsub(answer, repl, alphabet[j])
				end
			end
		end
		print(answer)
		for i = 1, vars do
			io.write(alphabet[i])
			io.write(" = ")
			io.write(variables[i])
			if(i ~= vars)
			then
				io.write(", ")
			end
		end
		
		break
	end
end