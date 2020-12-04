int pow(int left, int right) {
  int ans = 1;
  while (right) {
    if (right & 1)
      ans *= left;
    left *= left;
    right >>= 1;
  }
  return ans;
}