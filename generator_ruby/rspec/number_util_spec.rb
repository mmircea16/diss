require "../lib/number_util.rb"
require "rspec"
describe NumberUtil do
  
  before :all do
    @util = NumberUtil.new
  end
  
  it "should return correct value for 0's representation in unsigned binary" do
    @util.unsigned_binary_to_float("0.0").should eq(0)
    @util.unsigned_binary_to_float("0.0000").should eq(0)
    @util.unsigned_binary_to_float(".00").should eq(0)
  end
  
  it "should return correct value for sub-unitar values in unsigned binary" do
    
    @util.unsigned_binary_to_float("0.1").should eq(0.5)
    @util.unsigned_binary_to_float("0.0010").should eq(0.125)
    @util.unsigned_binary_to_float(".101").should eq(0.625)
    @util.unsigned_binary_to_float("00.01101").should eq(0.40625)
    @util.unsigned_binary_to_float("0.0010101100").should eq(0.16796875)
    
  end
  
  it "should retun correct values for integer representation in unsigned binary" do
    @util.unsigned_binary_to_float("1.0").should eq(1)
    @util.unsigned_binary_to_float("11.000").should eq(3)
    @util.unsigned_binary_to_float("1101.00").should eq(13)
    @util.unsigned_binary_to_float("101101.0").should eq(45)
    @util.unsigned_binary_to_float("10101101.000000000").should eq(173)
  end
  
  it "should return correct values for real numbers with fractional and integer part diff from 0" do
    @util.unsigned_binary_to_float("1.01").should eq(1.25)
    @util.unsigned_binary_to_float("101.011").should eq(5.375)
    @util.unsigned_binary_to_float("1001.1010").should eq(9.625)
    @util.unsigned_binary_to_float("101101.01101").should eq(45.40625)
    @util.unsigned_binary_to_float("10101101.0010101100").should eq(173.16796875)
  end
  
end