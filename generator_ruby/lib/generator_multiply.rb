require "./generator.rb"

class GeneratorMultiply < Generator
 
 attr_accessor :test_title
 
 def initialize options
    init_generator() 
    @test_file_name = "#{@path_to_tests_folder}/#{options["test_file_name"]}"
    @no_of_operands = 2
    @test_title = options["title"]
    @type_of_operands = "FIXED POINT BINARY"
    @type_of_result = "FIXED POINT BINARY"
    @saturated = options["saturated"]
    @operand_type = options["type"]
 end
 
 def generate_test test_no
     test = {}
     test["test_no"] = test_no
     
     case @operand_type
     when "8_8":
       range = 2**8
       min = - 2**7
       max = 2**7 - 2**(-8)
       t1 = @gen.generate_fixed_point(8,8)
       t2 = @gen.generate_fixed_point(8,8)  
     when "16_16":
       range = 2**16
       min = - 2**15
       max = 2**15 - 2**(-16)
       t1 = @gen.generate_fixed_point(16,16)
       t2 = @gen.generate_fixed_point(16,16)
     when "8_24":
       range = 2**8
       min = - 2**7
       max = 2**7 - 2**(-24)
       t1 = @gen.generate_fixed_point(8,24)
       t2 = @gen.generate_fixed_point(8,24)
     when "24_8":
       range = 2**24
       min = - 2**23
       max = 2**23 - 2**(-8)
       t1 = @gen.generate_fixed_point(24,8)
       t2 = @gen.generate_fixed_point(24,8)      
     else 
       
     end    
       
     
     test["first_operand"] = t1
     test["second_operand"] = t2
       
     t=0
     r =[]
    # if @operand_type == "8_8"
    #   t = (@util.signed_binary_to_float(t1)*@util.signed_binary_to_float(t2))
    #   r = [t.floor,t-t.floor]
    # else
       r = @util.multiply(@util.signed_binary_to_float(t1),@util.signed_binary_to_float(t2))
    # end
       
    
#     puts "#{test_no}----"
#     puts @util.signed_binary_to_float(t1)
#     puts @util.signed_binary_to_float(t2)
#     puts r
     rr = 0;
     if @saturated
      
       if r[0] >= max
         r = [max.floor,max - max.floor]
       end
       if r[0] < min
         r = [min.floor,min - min.floor]
       end
  
     else 
       
     end
     
     
     
     rez = ""
     case @operand_type
     when "8_8":
       rez = @util.float_to_signed(r[0],16,8)[-17..-9]+@util.float_to_signed(r[1],8,8)[-8..-1]
     when "16_16":
       rez = @util.float_to_signed(r[0],32,16)[-33..-17]+@util.float_to_signed(r[1],32,16)[-16..-1]
     when "8_24":
       rez = @util.float_to_signed(r[0],16,24)[-33..-25]+@util.float_to_signed(r[1],16,24)[-24..-1]
     when "24_8":
       rez = @util.float_to_signed(r[0],48,8)[-33..-9]+@util.float_to_signed(r[1],24,8)[-8..-1]
     end
 
     test["result"] = rez 
     
     return test
   end
 
 def make_tests
   write_metadata()
   (0..100).each do |k|
      test_hash = generate_test(k)
      write_test(test_hash)
   end
  end
 
end

