#CS 431
#Language Julia
#lightning bolt
#Compile: julia filename

using Random
using Dates

function main()
	blank = rand(0:49)
	n = 0
	loop = 0
	direction = 0
	start = 0
	
	#If start is 55sec or over will wait 5 seconds so the math will be correct
	while true
		start = Dates.format(now(), "SS")
		start = (parse(Float64, start))
		if start > 55
			sleep(5)
		else
			break
		end
	end
	time = 0
	
	#Loops for 5 seconds and print lightning bolt
	while time < 5.0
		for n in 0:blank
			print(" ")
		end

		if direction == 1
			println("\\")
		elseif direction == 0
			println("|")
		elseif direction == -1
			println("/")
		end
		
		prev_direction = direction
		while true
			if blank == 0
				direction = rand(0:1)
			elseif blank == 49
				direction = rand(-1:0)
			else 
				direction = rand(-1:1)
			end
			
			if prev_direction == 0
				break
			end
			if direction == 0
				break
			end
			if prev_direction == direction
				break
			end
		end
		blank = blank + direction
		curr = Dates.format(now(), "SS")
		curr = (parse(Float64, curr))
		
		time = curr - start
	end
end

main()
  