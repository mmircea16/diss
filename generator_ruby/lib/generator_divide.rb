require "./generator.rb"

class GeneratorDivide < Generator
 
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
 
 def generate_test(test_no,type = 0)
     test = {}
     test["test_no"] = test_no
     
     int_size = 0
     fract_size = 0
       
     case @operand_type
     when "8_8":
       range = 2**8
       min = - 2**7
       max = 2**7 - 2**(-8)
       int_size = 8
       fract_size = 8  
     when "16_16":
       range = 2**16
       min = - 2**15
       max = 2**15 - 2**(-16)
       int_size = 16
       fract_size = 16
     when "8_24":
       range = 2**8
       min = - 2**7
       max = 2**7 - 2**(-24)
       int_size = 8
       fract_size = 24
     when "24_8":
       range = 2**24
       min = - 2**23
       max = 2**23 - 2**(-8)
       int_size = 24
       fract_size = 8
     else 
       
     end    
       
     case type
     when 0:
       t1_min = 0;t1_max = 0;
       t2_min = 0;t2_max = 0;
     when 1:
       t1_min = -1;t1_max = 1;
       t2_min = (max/2).floor;t2_max = max;
     when 2:
       t1_min = -1;t1_max = 1;
       t2_min = min;t2_max = (min/2).floor;
     when 3:
       t2_min = -1;t2_max = 1;
       t1_min = (max/2).floor;t1_max = max;
     when 4:
       t2_min = -1;t2_max = 1;
       t1_min = min;t1_max = (min/2).floor;
     end
     
     t1 = @gen.generate_fixed_point(int_size,fract_size,t1_min*2**fract_size,t1_max*2**fract_size)
     t2 = @gen.generate_fixed_point(int_size,fract_size,t2_min*2**fract_size,t2_max*2**fract_size)
     
     test["first_operand"] = t1
     test["second_operand"] = t2
      
     puts "#{t2_min*2**fract_size} --  #{t2_max*2**fract_size}"  
     
     while @util.signed_binary_to_float(t2)==0
       t2 = @gen.generate_fixed_point(int_size,fract_size,0,0)
     end  
       

         
     r =  @util.signed_binary_to_float(t1)*1.0/ @util.signed_binary_to_float(t2); 
     puts "?: #{r} "     
     
     if @saturated
       if r<=min 
         r = min
       end
       
       if r>=max
         r = max
       end
     end
     puts "??: #{r} " 
#     puts "#{test_no}----"
#     puts @util.signed_binary_to_float(t1)
#     puts @util.signed_binary_to_float(t2)
#     puts r
#     rr = 0;
#     if @saturated
#      
#       if r[0] >= max
#         r = [max.floor,max - max.floor]
#       end
#       if r[0] < min
#         r = [min.floor,min - min.floor]
#       end
#  
#     else 
#       
#     end
      
     
     rez = ""
     case @operand_type
     when "8_8":
      # rez = @util.float_to_signed(r,16,8)[8..-1];
       rez = @util.float_to_signed(r,8,8)
     when "16_16":
       #rez = @util.float_to_signed(r,32,16)[16..-1];
       rez = @util.float_to_signed(r,16,16)
     when "8_24":
       #rez = @util.float_to_signed(r,32,24)[24..-1];
       rez = @util.float_to_signed(r,8,24)
     when "24_8":
       #rez = @util.float_to_signed(r,32,8)[8..-1];
       rez = @util.float_to_signed(r,24,8)
     end
 
     test["result"] = rez 
     
     return test
   end
 
 def make_tests
   write_metadata()
   test_no = 0
   (0..1000).each do |k|
      test_hash = generate_test(test_no)
      write_test(test_hash)
      test_no +=1
   end
   if @saturated
     (1..4).each do |p|
   
     (0..100).each do |k|
           test_hash = generate_test(test_no,p)
           write_test(test_hash)
           test_no +=1
      end 
      
     end
   end
  end
 
end
