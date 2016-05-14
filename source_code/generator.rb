#!/usr/bin/ruby

Complexity = ARGV[0].to_i + 1
Lenght = ARGV[1].to_i
Density = ARGV[2].to_i
Gap = 10 
Marge = Gap * Complexity / 10
Gap_w = 1 + (Gap.to_f / 100.0 * Density.to_f).to_i

def puts_error(str)
	puts "##generator_error"
	puts str
end

class Room
	def initialize(name = ROOM, x = 0, y = 0)
		@name = name
		@x = x
		@y = y
	end
	def print
		puts "#{@name} #{@x} #{@y}"
	end

	def x
		@x
	end
	def y
		@y
	end
	def name
		@name
	end
end

class Line
	@@total = 0

	def initialize(y = 0, index = 0)
		@@total += 1
		if index % 2 == 0
			@x = Gap_w / 2
		else
			@x = 0
		end
		@y = y
		@room = []
		add_rooms
	end

	def add_room(numero)
		tmp = Room.new("ROOM_#{@@total}_#{numero}", @x, @y)
		@room << tmp
	end

	def add_rooms
		new = 0
		for i in (0..Complexity)
			if rand(100) < Density || (i == Complexity && new == 0)
				add_room(i)
				new += 1
			end
			@x += Gap_w
		end
	end

	def print
		for r in @room
			r.print
		end
	end

	def next_room(actual_room)
		if actual_room == nil
			return @room[0]
		end
		if actual_room == @room[-1]
			return nil
		end
		for r in @room
			if (r == actual_room)
				index = @room.find_index(r)
				return @room[index + 1]
			end
		end
	end
			
	def room(n)
		return @room[n]
	end

	def room
		return @room
	end
end

class Graph
	def initialize
		@index_line = 1
		@line = []
		@begin = Room.new("BEGIN_ROOM", (Complexity + 1) * Gap_w / 2, 0);
		@end = Room.new("EXIT_ROOM", (Complexity + 1) * Gap_w / 2, (Lenght + 1) * Gap + Marge * 2);
		add_lines
	end

	def add_line
		@line << Line.new(@index_line * Gap + Marge, @index_line)
	end

	def add_lines
		while @index_line <= Lenght
			add_line
			@index_line += 1
		end
	end

	def print
		puts ARGV[3]
		puts "##start"
		@begin.print
		for l in @line
			l.print
		end
		puts "##end"
		@end.print
	end

	def next_line(actual_line)
		if actual_line == nil
			return @line[0]
		end
		if actual_line == @line[-1]
			return nil
		end
		for l in @line
			if (l == actual_line)
				index = @line.find_index(l)
				return @line[index + 1]
			end
		end
	end

	def print_link(line)
		actual_room = line.next_room(nil)
		next_room = line.next_room(actual_room)
		line2 = next_line(line)
		if (line2 == nil)
			return
		end
		r = line2.next_room(nil)
		while r != nil 
			while next_room != nil && (r.x - actual_room.x).abs > (r.x - next_room.x).abs
				actual_room = next_room
				next_room = line.next_room(next_room)
				if next_room != nil && rand(400) < Density
					puts "#{next_room.name}-#{actual_room.name}"
				end
			end
			puts "#{r.name}-#{actual_room.name}"
			r = line2.next_room(r)
		end
		actual_room = line.next_room(nil)
		next_room = line.next_room(actual_room)
		line2 = next_line(line2)
		if (line2 == nil)
			return
		end
		r = line2.next_room(nil)
		while r != nil 
	 		while next_room != nil && (r.x - actual_room.x).abs > (r.x - next_room.x).abs
				actual_room = next_room
				next_room = line.next_room(next_room)
			end
			if rand(300) < Density
				puts "#{r.name}-#{actual_room.name}"
			end
				r = line2.next_room(r)
		end
	end

	def print_links
		for r in @line[0].room
			puts "#{r.name}-#{@begin.name}"
		end
		for l in @line
			print_link(l)
		end
		for r in @line[-1].room
			puts "#{r.name}-#{@end.name}"
		end
	end

	def line(n)
		@line[n]
	end
		
end

if ARGV.length != 4
	puts_error "Need 4 arguments (complexity, length, density and number of ants)."
	exit
end
if Complexity <= 0
	puts_error "Complexity must be positive."
	exit
end
if Lenght <= 0
	puts_error "Length must be positive."
	exit
end
if Density < 0 || Density > 100
	puts_error "Density must be between 0 ant 100."
	exit
end
if ARGV[3].to_i <= 0
	puts_error "Number of ants must be positive."
	exit
end
graph = Graph.new()
graph.print
graph.print_links
min = 0x44
max = 0xFF
puts "##red/#{min}/#{max}"
min = 0x00
max = 0x44
puts "##green/#{min}/#{max}"
min = 0x44
max = 0xFF
puts "##blue/#{min}/#{max}"
puts "end"
