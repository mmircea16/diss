require "./number_util.rb"

class NumberGenerator
 
 def generate_fixed_point_8_8
  # random = Random.new()
#   x = rand(2**16)
#   p = 0
#   s = ""
#   while (x>0)
#     s += (x%2).to_s
#	 x /= 2
#	 p += 1
#	 if (p==8) 
#	  s +="."
#	 end
#   end
#   (p..15).each do |k|
#     s += "0"
#   end
#   s.reverse!
#   return s
   generate_fixed_point(8,8);
 end
 
 def generate_fixed_point(int_size, fract_size,min = 0,max=0)
   if (min==max) and (min==0)
     x = rand(2**(int_size+fract_size))-2**(int_size+fract_size-1)
   else
     x = min + rand(max-min)
     puts "--- #{x}  #{min} #{max-min}"
   end
 
   
   x = x*1.0/(2**fract_size*1.0)

   util = NumberUtil.new
  # puts (x>=2**(int_size+fract_size-1)?x-2**(int_size+fract_size):x)/(2**fract_size * 1.0)
#   p = 0
#   s = ""
#   while (x>0)
#     s += (x%2).to_s
#     x /= 2
#     p += 1
#     if (p==fract_size) 
#      s +="."
#     end
#   end
#   
#   if p<fract_size
#     (p..fract_size-1).each do |k|
#       s+="0"
#     end
#     s+="."
#     p=fract_size
#   end
#   t = fract_size+int_size - 1
#   (p..t).each do |k|
#       s += "0"
#   end
#   
#   s.reverse!
   s = util.float_to_signed(x,int_size,fract_size)
   return s   
 end
 
 def generate_float min,max
 #random = Random.new
 x = rand
 x *= (max-min)
 x += min
 x = x.floor
 return x
end
 
end


