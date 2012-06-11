class NumberGenerator
 
 def generate_fixed_point_8_8
   random = Random.new()
   x = random.rand(0...2**16)
   p = 0
   s = ""
   while (x>0)
     s += (x%2).to_s
	 x /= 2
	 p += 1
	 if (p==8) 
	  s +="."
	 end
   end
   (p..15).each do |k|
     s += "0"
   end
   s.reverse!
   return s
 end
 
 def generate_float min,max
 random = Random.new
 x = random.rand
 x *= (max-min)
 x += min
 return x
end
 
end


