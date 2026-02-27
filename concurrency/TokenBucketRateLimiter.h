//
// Created by agrwl on 19-07-2025.
//

#ifndef CONCURRENT_RATE_LIMITER_H
#define CONCURRENT_RATE_LIMITER_H



// There are 3 concepts to keep in mind.
// 1. Thread-safety
// 2. Type of rate limiter
// a. Leaky Bucket
// b. Token Bucket, allows for a th


class TokenBucketRateLimiter {
public:
  TokenBucketRateLimiter(int capacity, int rate_per_sec);

  bool Acquire();

private:
  void Refill();

  const int capacity_;
  const int rate_per_sec_;

  int tokens_;
  int last_refill_;
};



#endif //CONCURRENT_RATE_LIMITER_H
