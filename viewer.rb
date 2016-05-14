require 'gosu'

Rnormal = 1
Rstart = 0
Rend = 2
W = 1500
H = 1500
Number_color_ant = 1000
Color_tube = 0x2200CCFF
Color_room = 0xFF008844
Marge = 20

def	get_next_line(window)
	line = gets
	if line == nil
		return nil
	end
	line = line.chomp
	if line[0] == '#'
		return line
	end
	if line.include?("ERROR")
		puts line
		window.close
		exit
	end
	return line
end

class Circle
	  attr_reader :columns, :rows

	def initialize radius
		@columns = @rows = radius * 2
		lower_half = (0...radius).map do |y|
		x = Math.sqrt(radius**2 - y**2).round
		right_half = "#{"\xff" * x}#{"\x00" * (radius - x)}"
		"#{right_half.reverse}#{right_half}"
		end.join
		@blob = lower_half.reverse + lower_half
		@blob.gsub!(/./) { |alpha| "\xff\xff\xff#{alpha}"}
	end

	def to_blob
		@blob
	end
end


class Coor
	def initialise(x, y)
		@x = x
		@y = y
	end
end

class Room
	attr_accessor :x
	attr_accessor :y
	attr_accessor :name
	attr_reader :type

	def initialize(name, x, y, rtype)
		@name = name
		@x = x.to_f
		@y = y.to_f
		@type = rtype
		@link = Array.new
		min_x = x
	end

	def add_link(room)
		@link.push(room)
	end

	def draw(window)
		@link.each do |r|
			window.draw_line(@x, @y, Color_tube, r.x, r.y, Color_tube)
		end
		window.draw_rectangle(@x - 1.2, @y - 1.2, 2.5, 2.5, Color_room)
	end

	def center min_x, min_y, max_x, max_y
		w = max_x - min_x
		h = max_y - min_y
		void_space_w = (W - Marge * 2) - w
		if void_space_w < 0
			void_space_w = 0
		end
		void_space_h = (H - Marge * 2) - h
		if void_space_h < 0
			void_space_h = 0
		end
		marge_w = Marge + (void_space_w / 2)
		marge_h = Marge + (void_space_h / 2)
		@x = ((@x - min_x) / (max_x - min_x)) * (W - (marge_w * 2)) + marge_w
		@y = ((@y - min_y) / (max_y - min_y)) * (H - (marge_h * 2)) + marge_h
	end

	def draw_ant(window, id)
		window.draw_circle(@x.to_i, @y.to_i, window.color_ant[id % Number_color_ant]) end
end

class Anthill

	attr_accessor :min_x
	attr_accessor :min_y
	attr_accessor :max_x
	attr_accessor :max_y
	attr_accessor :new_turn
	attr_accessor :line_update
	attr_accessor :total

	def change_red(window, line)
		split = line.split('/')
		if split.length != 3
			return
		end
		window.min_red = split[1].to_i
		window.max_red = split[2].to_i
	end

	def change_green(window, line)
		split = line.split('/')
		if split.length != 3
			return
		end
		window.min_green = split[1].to_i
		window.max_green = split[2].to_i
	end

	def change_blue(window, line)
		split = line.split('/')
		if split.length != 3
			return
		end
		window.min_blue = split[1].to_i
		window.max_blue = split[2].to_i
	end

	def special_command(line, window)
			if line.index("##red") == 0
				change_red(window, line)
			elsif line.index("##blue") == 0
				change_blue(window, line)
			elsif line.index("##green") == 0
				change_green(window, line)
			end
	end

	def initialize(window)
		@new_turn = false
		@line_update = nil
		@room = Hash.new
		@min_x = nil
		@min_y = nil
		@max_x = nil
		@max_y = nil
		@end_ants = 0
		@total = 0
		next_type = Rnormal
		continue = true
		line = get_next_line(window)
		while line[0] == '#'
			special_command(line, window)
			line = get_next_line(window)
		end
		@start_ants = line.to_i
		@actual_start_ants = @start_ants
		line = get_next_line(window)
		while continue == true
			continue = false

			split = line.split(' ')
			if split.length == 3 && line[0] != '#'
				continue = true
				r = add_room(split, next_type)
				if next_type == Rstart
					@begin_room = r
				elsif next_type == Rend
					@end_room = r
				end
			end

			split = line.split('-')
			if split.length == 2 && line[0] != '#'
				continue = true
				add_link(split)
				split.reverse!
				add_link(split)
			end

			if line[0] == '#'
				continue = true
			end

			if line == "##start"
				next_type = Rstart
			elsif line == "##end"
				next_type = Rend
			elsif line[0] != '#'
				next_type = Rnormal
			end

			special_command(line, window)

			if continue == true
				line = get_next_line(window)
			end
		end
		center
	end

	def add_room(split, rtype)
		@room[split[0]] = Room.new(split[0], split[1], split[2], rtype)
		r = @room[split[0]]
		if @min_x == nil || r.x < @min_x
			@min_x = r.x
		end
		if @max_x == nil || r.x > @max_x
			@max_x = r.x
		end
		if @min_y == nil || r.y < @min_y
			@min_y = r.y
		end
		if @max_y == nil || r.y > @max_y
			@max_y = r.y
		end
		return r
	end

	def add_link(split)
		@room[split[0]].add_link(@room[split[1]])
		@room[split[1]].add_link(@room[split[0]])
	end

	def center
		@room.each do |key, room|
			room.center @min_x, @min_y, @max_x, @max_y
		end
	end
	
	def draw(window)
		@room.each do |key, room|
			room.draw(window)
		end
	end

	def draw_update(window)
		return if @line_update == nil
		draw_ants @line_update, window
		window.draw_txt(@actual_start_ants.to_s, @begin_room.x, @begin_room.y)
		window.draw_txt(@end_ants.to_s, @end_room.x, @end_room.y)
	end


	def draw_ants(line, window)
		split = line.split(' ')
		if split.length <= 0
			return
		end
		for ant in split
			split_ant = ant.split('-')
			if split_ant.length == 2
				split_ant[0][0] = ''
				id = split_ant[0].to_i
				@room[split_ant[1]].draw_ant(window, id)
				if @room[split_ant[1]].type == Rend && @new_turn == true
					@end_ants += 1
				end
				if @start_ants - id < @actual_start_ants
					@actual_start_ants = @start_ants - id
				end
			end
		end
	end

end

class GameWindow < Gosu::Window

	attr_reader	:color_ant
	attr_writer :min_red
	attr_writer :max_red
	attr_writer :min_green
	attr_writer :max_green
	attr_writer :min_blue
	attr_writer :max_blue

	def initialize
		super W, H
		self.caption = "Lem-in viewer"
		@min_red = 0x00
		@max_red = 0xFF
		@min_green = 0x00
		@max_green = 0xFF
		@min_blue = 0x00
		@max_blue = 0xFF
		@r = 3
		@img = Gosu::Image.new(self, Circle.new(@r), false)
		@ah = Anthill.new(self)
		@last_time = Time.now
		@delay = 0.1
		@pause = true
		@next = false
		@font = Gosu::Font.new(40)
		@color_ant = Array.new
		for i in (1..Number_color_ant)
			@color_ant << rand_color
		end
	end

	def rand_composant(min, max)
		if min < 0
			min = 0
		end
		if max > 0xFF
			max = 0xFF
		end
		if max <= min
			c = 0
		else
			c = rand(max - min) + min
		end
	end

	def rand_color
		r = rand_composant(@min_red, @max_red)
		g = rand_composant(@min_green, @max_green)
		b = rand_composant(@min_blue, @max_blue)
		color = 0xFF000000 + b + g * 0x100 + r * 0x10000
	end

	def draw_circle(x, y, c)
		x -= @r / 2
		y -= @r / 2
		@img.draw(x, y, 0, 1, 1, c)
	end

	def draw_rectangle(x, y, w, h, c)
		draw_quad(x, y, c, x + w, y, c, x + w, y + h, c, x, y + h, c)
	end

	def draw_txt(txt, x, y)
		x -= @font.text_width(txt) / 2
		y -= @font.height / 2
		@font.draw(txt, x, y, 0)
	end

	def button_down(id)
		case id
		when Gosu::KbEscape
			close
			exit
		when Gosu::KbUp
			@delay -= 0.02
			if @delay < 0.0
				@delay = 0.0
			end
		when Gosu::KbDown
			@delay += 0.02
		when Gosu::KbN
			@next = true
		when Gosu::KbSpace
			if @pause == true
				@pause = false
			else
				@pause = true
			end
		end
	end

	def update
		@ah.new_turn = false
		return if @pause == true && @next == false
		return if Time.now - @last_time < @delay
		@last_time = Time.now
		@ah.new_turn = true
		@ah.line_update = get_next_line(self)
		if @ah.line_update != nil
			@ah.total += 1
		end
		@next = false
	end

	def draw
		@font.draw("TOTAL = #{@ah.total}", Marge, Marge, 0)
		@ah.draw(self)
		@ah.draw_update(self)
	end

end

window = GameWindow.new
window.show
